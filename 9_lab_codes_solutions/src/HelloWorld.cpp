#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    // What is my rank (process ID)?
    int myRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    // How many processes do we have in total?
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    cout << "My rank: " << myRank << endl;

    if (myRank == 0) {
        cout << "Total number of processes: " << size << endl;
    }


    MPI_Finalize();
}
