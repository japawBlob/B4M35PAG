#include <chrono>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <functional>
#include <vector>
<<<<<<< HEAD
=======
#include <omp.h>
>>>>>>> ddb049ab6f262d2f5bccc3f2cd27ce27be0737bf
#include <thread>

using namespace std;
using namespace std::chrono;

int blob = 0;

class LU {
public:
    void readMatrixFromInputFile(const string &inputFile) {
        ifstream bin(inputFile.c_str(), ifstream::in | ifstream::binary);
        if (bin.fail()) {
            throw invalid_argument("Cannot open the input file!");
        }

        uint64_t n = 0;
        bin.read((char *) &n, sizeof(uint64_t));
        A.resize(n, vector<double>(n, 0.0));
        L = U = A;
        for (uint64_t r = 0; r < n; ++r) {
            bin.read((char *) A[r].data(), n * sizeof(double));
        }
    }

    void writeResultsToOutputFile(const string &outputFile) {
        ofstream bout(outputFile.c_str(), ofstream::out | ofstream::binary);
        if (bout.fail()) {
            throw invalid_argument("Cannot open the output file!");
        }

        uint64_t n = A.size();
        for (uint64_t r = 0; r < n; ++r) {
            bout.write((char *) L[r].data(), n * sizeof(double));
        }
        for (uint64_t r = 0; r < n; ++r) {
            bout.write((char *) U[r].data(), n * sizeof(double));
        }
    }
 /*   void decompose() {
        auto n = A.size();
        for (int k = 0; k < n; ++k) {
            for (int j = k; j < n; ++j) {
                U[k][j] = A[k][j];
            }
            L[k][k] = 1;
            for (int i = k+1; i < n; ++i) {
                L[i][k] = A[i][k] / U[k][k];

            }
            for (int i = k+1; i < n; ++i) {
                for (int j = k+1; j < n; ++j) {
                    A[i][j] = A[i][j] - L[i][k] * U[k][j];
                }
            }
        }
    }*/
    void decompose() {
        auto n = A.size();
        bool blob = true;
#pragma omp parallel for shared (A,L,U)
        for (int k = 0; k < n; ++k) {
            U[k][k] = A[k][k];
            auto devider = U[k][k];




            //thread thread2(&LU::secondPart, this, k, n, devider);
            //thread thread1(&LU::firstPart, this, k, n);
            firstPart(k, n);
            secondPart(k, n, devider);
            L[k][k] = 1;
            //thread1.join();
            //thread2.join();


            //secondPart(k, n, devider);
            //unsigned numberOfThreads = 2/*thread::hardware_concurrency()*/;
            //unsigned chunkSize = n/numberOfThreads;
            //cout << chunkSize << endl;
            unsigned chunkSize = n/2;
            int start = 0, end = chunkSize;

            /*for (int i = 0; i < numberOfThreads-1; ++i) {
                thirdPart(k, n, start, end);
                start += chunkSize;
                end += chunkSize;
            }*/
            thirdPart(k, n, k+1+start, n);
            /*thirdPart(k, n, k+1+start, start + chunkSize);
            start += chunkSize-1;
            thirdPart(k, n, k+1+start, n);*/
        }
    }


private:

    vector<vector<double>> A;
    vector<vector<double>> L;
    vector<vector<double>> U;

    friend ostream &operator<<(ostream &, const LU &);

    void firstPart(int k, unsigned n){
        for (int j = k+1; j < n; ++j) {
            U[k][j] = A[k][j];
        }
    }
    void secondPart(int k, unsigned n, double devider){
        for (int i = k+1; i < n; ++i) {
            //L[i][k] = A[i][k] / devider;
            L[k][i] = A[i][k] / devider;
        }
    }
    void thirdPart(int k, unsigned n, int start, int end){
        for (int i = start; i < end; ++i) {
            cout << "i: " << i << endl;
            for (int j = k+1; j < n; ++j) {
                A[i][j] = A[i][j] - L[k][i] * U[k][j];
                //cout << "here" << blob++ << endl;
            }
        }
        cout << "end" << endl;
        blob = 0;
    }
};

// Print the matrices A, L, and U of an LU class instance.
ostream &operator<<(ostream &out, const LU &lu) {
    function<void(const vector <vector<double>> &)> printMatrix = [&](const vector <vector<double>> &M) {
        int n = M.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                out << " " << setw(10) << M[i][j];
            }
            out << endl;
        }
    };

    out << "Matrix A:" << endl;
    printMatrix(lu.A);
    out << endl << "Lower matrix:" << endl;
    printMatrix(lu.L);
    out << endl << "Upper matrix:" << endl;
    printMatrix(lu.U);

    return out;
}

int main(int argc, char *argv[]) {
    if (argc <= 1 || argc > 3) {
        cout << "LU decomposition of a square matrix." << endl;
        cout << endl << "Usage:" << endl;
        cout << "\t" << argv[0] << " inputMatrix.bin [output.bin]" << endl;
        return 1;
    }

    string inputFile = argv[1];
    string outputFile;
    if (argc == 3) {
        outputFile = argv[2];
    }

    LU lu;
    lu.readMatrixFromInputFile(inputFile);

    auto start = high_resolution_clock::now();
    lu.decompose();
    auto runtime = duration_cast<duration<double>>(high_resolution_clock::now()-start).count();

    cout << "Computational time: " << runtime << "s" << endl;

    // Decomposition is printed only if the output file is not written.
    if (outputFile.empty()) {
        cout << lu << endl;
    }
    else {
        lu.writeResultsToOutputFile(outputFile);
    }

    return 0;
}

