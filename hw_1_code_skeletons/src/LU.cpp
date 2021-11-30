#include <chrono>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <functional>
#include <vector>
#include <thread>
#include <algorithm>
#include <condition_variable>
#include <mutex>
#include <atomic>


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

    /// Přikládám i funkci Decompose1, kte je nezdařilý pokus o paralelizaci. Bohužel jsem si ji nechal na poslední chvíli.
    /// Příště budu pečlivější...:)
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
    mutex mut;
    mutex mut2;
    condition_variable cv;
    bool ready = false;
    bool fine = false;
    unsigned numberOfThreads;

    void print_id (int id) {
        std::unique_lock<std::mutex> lck(mut);
        while (!ready) cv.wait(lck);
        // ...
        std::cout << "thread " << id << '\n';
    }

    void decompose1() {
        mut2.lock();
        auto n = A.size();
        //std::unique_lock<std::mutex> lck(mut);
        numberOfThreads = thread::hardware_concurrency();
        cout << "number of threads " << numberOfThreads << endl;

        thread threads[numberOfThreads];

        while (n < numberOfThreads){
            numberOfThreads = numberOfThreads/2;
            if(numberOfThreads == 0){
                numberOfThreads = 1;
                break;
            }
        }
        int chunkSize = n/numberOfThreads;
        int start = 1;
        int end = start + chunkSize;
        int threadNumber;
        for (threadNumber = 0; threadNumber < numberOfThreads-1; ++threadNumber) {
            cout << "thread created" << endl;
            if(end > n) end = n;
            if (start>end) break;
            threads[threadNumber] = thread(&LU::thirdPart, this, 1, n, start, end);
            //threads[threadNumber] = thread(&LU::print_id, this, threadNumber);

            start += chunkSize;
            end += chunkSize;
        }
        threads[threadNumber] = thread(&LU::thirdPart, this, 1, n, start, n);
        //threads[threadNumber] = thread(&LU::print_id, this, threadNumber);



        for (int k = 0; k < n; ++k) {
            U[k][k] = A[k][k];
            auto devider = U[k][k];
            firstPart(k, n);
            secondPart(k, n, devider);
            L[k][k] = 1;


            cout << "here " << endl;
            ready = true;
            cv.notify_all();
            mut2.lock();
            cout << "here " << endl;

            //thirdPart(k, n, start, n);
            //thread thread2(&LU::thirdPart, this, k, n, start, end);
            //thread thread3(&LU::thirdPart, this, k, n, start, end);
            //thread thread4(&LU::thirdPart, this, k, n, start, end);
            //thread thread5(&LU::thirdPart, this, k, n, start, n);

            /*thread2.join();
            thread3.join();
            thread4.join();
            thread5.join();*/
        }
        fine = true;
        cv.notify_all();
        for (int i=0; i<numberOfThreads; ++i) {
            threads[i].join();
        }

        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                L[j][i] = L[i][j];
                L[i][j] = 0;
            }
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
    mutex mut3;
    unsigned barrierCounter = 0;
    condition_variable barrier;

    void thirdPart(int k, unsigned n, int start, int end){
        std::unique_lock<std::mutex> lck(mut);
        std::unique_lock<std::mutex> lk(mut3);
        cout << "blobanec "  << endl;
        lk.unlock();
        while(!fine){
            while (!ready) cv.wait(lck);
            if (fine){
                break;
            }
            cout << "I am thread " << endl;
            lck.unlock();
            for (int i = start; i < end; ++i) {
                cout << "i: " << i << endl;
                for (int j = k + 1; j < n; ++j) {
                    A[i][j] = A[i][j] - L[k][i] * U[k][j];
                    //A[i][j] = A[i][j] - L[i][k] * U[k][j];
                }
            }
            lk.lock();
            ready = false;
            barrierCounter++;
            cout << "barCounter : " << barrierCounter << endl;
            if(barrierCounter == numberOfThreads){
                mut2.unlock();
                barrierCounter = 0;
            }
            lk.unlock();
            cout << "here : " << endl;
            k++;
        }
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

