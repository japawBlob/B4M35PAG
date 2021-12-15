#include <iostream>
#include <string>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int myRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    if (myRank == 0) {
        // Sends message.
        string message = "IDKFA";

        MPI_Request request;
        MPI_Isend(
                message.c_str(),
                message.length() + 1,   // +1 is for '\0'
                MPI_CHAR,
                1,
                0,
                MPI_COMM_WORLD,
                &request);

        MPI_Wait(&request, MPI_STATUS_IGNORE);
    } else if (myRank == 1) {
        // Receives message.
        constexpr int bufSize = 256;
        char buf[bufSize];

        MPI_Request request;
        MPI_Irecv(
                buf,
                bufSize,  // We "do not know" the size of message, receive at most bufSize elements.
                MPI_CHAR,
                0,
                MPI_ANY_TAG,
                MPI_COMM_WORLD,
                &request);

        MPI_Status status;
        MPI_Wait(&request, &status);

        int receivedSize;
        MPI_Get_count(&status, MPI_CHAR, &receivedSize);

        cout << "Received message size: " << receivedSize << endl;
        cout << "Received message content: " << string(buf) << endl;
    }


    MPI_Finalize();
}
