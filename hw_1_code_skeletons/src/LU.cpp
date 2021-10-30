#include <chrono>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <functional>
#include <vector>

using namespace std;
using namespace std::chrono;

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

    void decompose() {
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
    }

private:

    vector<vector<double>> A;
    vector<vector<double>> L;
    vector<vector<double>> U;

    friend ostream &operator<<(ostream &, const LU &);
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

