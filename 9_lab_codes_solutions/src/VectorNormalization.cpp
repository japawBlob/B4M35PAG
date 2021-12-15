#include <iostream>
#include <vector>
#include <mpi.h>
#include <cmath>

#include "Utils.hpp"

using namespace std;

#define ROOT_PROCESS 0

double computeSumOfSquares(const vector<double> &u) {
    double sumSquares = 0;
    for (double x : u) {
        sumSquares += x * x;
    }
    return sumSquares;
}

double computeVectorLength(const vector<double> u) {
    return sqrt(computeSumOfSquares(u));
}

void divideByVectorLength(vector<double> &u, double vectorLength) {
    for (int i = 0; i < u.size(); i++) {
        u[i] /= vectorLength;
    }
}

vector<double> distributeInputVectorChunks(
        const vector<double> &u,
        const vector<int> &chunkSizes,
        const vector<int> &bases) {
    int childChunkSize = chunkSizes.back();
    int rootChunkSize = chunkSizes[ROOT_PROCESS];

    // First, we inform the slaves about the chunk size. According to that, slaves will allocate buffers to receive
    // their chunk of the vector.
    MPI_Bcast(&childChunkSize, 1, MPI_INT, ROOT_PROCESS, MPI_COMM_WORLD);

    // Second, distribute the vector chunks (the first chunk of size rootChunkSize is for the root process).
    vector<double> buf(rootChunkSize, 0);      // Root process will also receive its chunk.
    MPI_Scatterv(
            u.data(),
            chunkSizes.data(),
            bases.data(),
            MPI_DOUBLE,
            buf.data(),
            rootChunkSize,
            MPI_DOUBLE,
            ROOT_PROCESS,
            MPI_COMM_WORLD);

    return buf;
}

vector<double> receiveInputVectorChunk() {
    // Get the chunk size.
    int chunkSize;
    MPI_Bcast(&chunkSize, 1, MPI_INT, ROOT_PROCESS, MPI_COMM_WORLD);

    // Get the chunk of the input vector.
    vector<double> buf(chunkSize, 0);
    MPI_Scatterv(
            NULL,
            NULL,
            NULL,
            MPI_DOUBLE,
            buf.data(),
            chunkSize,
            MPI_DOUBLE,
            ROOT_PROCESS,
            MPI_COMM_WORLD);

    return buf;
}

double receiveVectorLength(double sumOfSquaresChunk) {
    double totalSumOfSquares = 0.0;
    MPI_Allreduce(
            &sumOfSquaresChunk,
            &totalSumOfSquares,
            1,
            MPI_DOUBLE,
            MPI_SUM,
            MPI_COMM_WORLD);

    return sqrt(totalSumOfSquares);
}

void sendProcessedVectorChunk(const vector<double> &uChunk) {
    MPI_Gatherv(
            uChunk.data(),
            uChunk.size(),
            MPI_DOUBLE,
            NULL,
            NULL,
            NULL,
            MPI_DOUBLE,
            ROOT_PROCESS,
            MPI_COMM_WORLD);
}

vector<double> receiveOutputVector(
        const vector<double> &uChunk,
        int outputVectorSize,
        const vector<int> &chunkSizes,
        const vector<int> &bases) {
    vector<double> buf(outputVectorSize, 0);
    MPI_Gatherv(
            uChunk.data(),
            uChunk.size(),
            MPI_DOUBLE,
            buf.data(),
            chunkSizes.data(),
            bases.data(),
            MPI_DOUBLE,
            ROOT_PROCESS,
            MPI_COMM_WORLD);

    return buf;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int myRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    int worldSize;
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

    if (myRank == ROOT_PROCESS) {
        vector<double> u = generateRandomVector(5000000);

        Stopwatch sw;
        sw.start();

        int childChunkSize = u.size() / worldSize;
        int rootChunkSize = u.size() - (childChunkSize * (worldSize - 1));

        vector<int> chunkSizes(worldSize, 0);
        vector<int> bases(worldSize, 0);
        for (int i = 0; i < worldSize; i++) {
            if (i == ROOT_PROCESS) {
                chunkSizes[i] = rootChunkSize;
                bases[i] = 0;
            }
            else {
                chunkSizes[i] = childChunkSize;
                bases[i] = rootChunkSize + (i - 1) * childChunkSize;
            }
        }

        vector<double> uChunk = distributeInputVectorChunks(u, chunkSizes, bases);
        double sumOfSquaresChunk = computeSumOfSquares(uChunk);
        double vectorLength = receiveVectorLength(sumOfSquaresChunk);
        divideByVectorLength(uChunk, vectorLength);
        auto uNorm = receiveOutputVector(uChunk, u.size(), chunkSizes, bases);

        sw.stop();
        cout << "MPI: " << sw.duration().count() << " ms, length " << computeVectorLength(uNorm) << endl;
    }
    else {
        vector<double> uChunk = receiveInputVectorChunk();
        double sumOfSquaresChunk = computeSumOfSquares(uChunk);
        double vectorLength = receiveVectorLength(sumOfSquaresChunk);
        divideByVectorLength(uChunk, vectorLength);
        sendProcessedVectorChunk(uChunk);
    }

    MPI_Finalize();

    return 0;
}
