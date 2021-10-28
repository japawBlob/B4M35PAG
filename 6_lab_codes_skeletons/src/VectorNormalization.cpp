#include <iostream>
#include <vector>
#include <omp.h>
#include <cmath>

#include "Utils.hpp"

using namespace std;

void normalizationSequential(vector<double> &u) {
    double sumSquares = 0;
    for (int i = 0; i < u.size(); i++) {
        sumSquares += u[i] * u[i];
    }

    double vectorLength = sqrt(sumSquares);
    for (int i = 0; i < u.size(); i++) {
        u[i] /= vectorLength;
    }
}

// Split the vector in two halves. Create two OpenMP 'sections', each processing one half (computation of sum of squares
// and then normalization of the elements).
void normalizationParallelSections(vector<double> &u) {
    int lastIndexInFirstHalf = (u.size() - 1) / 2;

    double leftHalfSumSquares = 0;
    double rightHalfSumSquares = 0;
    #pragma omp parallel num_threads(2)
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                // QUESTION: what would happen if we wrote directly to leftHalfSumOfSquares?
                // For the explanation, wait for the OpenMP lab 2 :).
                double halfSumSquares = 0.0;
                for (int i = 0; i <= lastIndexInFirstHalf; i++) {
                    halfSumSquares += u[i] * u[i];
                }
                leftHalfSumSquares = halfSumSquares;
            }

            #pragma omp section
            {
                double halfSumSquares = 0.0;
                for (int i = lastIndexInFirstHalf + 1; i < u.size(); i++) {
                    halfSumSquares += u[i] * u[i];
                }
                rightHalfSumSquares = halfSumSquares;
            }
        }

        double vectorLength = sqrt(leftHalfSumSquares + rightHalfSumSquares);

        #pragma omp sections
        {
            #pragma omp section
            {
                for (int i = 0; i <= lastIndexInFirstHalf; i++) {
                    u[i] /= vectorLength;
                }
            }

            #pragma omp section
            {
                for (int i = lastIndexInFirstHalf + 1; i < u.size(); i++) {
                    u[i] /= vectorLength;
                }
            }
        }
    }
}

// Use 'parallel for' for parallelization of sum of squares and element normalization. Use OpenMP 'critical' directive
// when computing the sum of squares.
void normalizationCriticalAndParallelFor(vector<double> &u) {
    double sumSquares = 0;
    #pragma omp parallel for
    for (int i = 0; i < u.size(); i++) {
        #pragma omp critical
        sumSquares += u[i] * u[i];
    }

    double vectorLength = sqrt(sumSquares);
    #pragma omp parallel for
    for (int i = 0; i < u.size(); i++) {
        u[i] /= vectorLength;
    }
}

// Use 'parallel for' for parallelization of sum of squares and element normalization. In one loop you should also use
// 'reduction', guess in which one?
void normalizationParallelForAndReduction(vector<double> &u) {
    double sumSquares = 0;
    #pragma omp parallel for reduction(+:sumSquares)
    for (int i = 0; i < u.size(); i++) {
        sumSquares += u[i] * u[i];
    }

    double vectorLength = sqrt(sumSquares);
    #pragma omp parallel for
    for (int i = 0; i < u.size(); i++) {
        u[i] /= vectorLength;
    }
}

// Use 'parallel for' for parallelization of sum of squares and element normalization. Use OpenMP 'atomic' directive
// when computing the sum of squares.
void normalizationParallelForAndAtomic(vector<double> &u) {

    double sumSquares = 0;
    #pragma omp parallel for reduction(+:sumSquares)
    for (int i = 0; i < u.size(); i++) {
        #pragma omp atomic update
        sumSquares += u[i] * u[i];
    }

    double vectorLength = sqrt(sumSquares);
    #pragma omp parallel for
    for (int i = 0; i < u.size(); i++) {
        u[i] /= vectorLength;
    }
}

// Use vectorization with 'simd' directive. You can also experiment with 'parallel for' and 'reduction'.
void normalizationParallelSimd(vector<double> &u) {
    double sumSquares = 0;
    #pragma omp parallel for simd reduction(+:sumSquares)
    for (int i = 0; i < u.size(); i++) {
        sumSquares += u[i] * u[i];
    }

    double vectorLength = sqrt(sumSquares);
    #pragma omp parallel for
    for (int i = 0; i < u.size(); i++) {
        u[i] /= vectorLength;
    }
}

int main() {
    vector<double> u = generateRandomVector(50000000);

    cout << "Length of the input vector: " << computeVectorLength(u) << endl;

    {
        vector<double> uCopy = u;
        Stopwatch sw;
        sw.start();
        normalizationSequential(uCopy);
        sw.stop();
        cout << "Sequential: " << sw.duration().count() << " ms, length " << computeVectorLength(uCopy) << endl;
    }

    {
        vector<double> uCopy = u;
        Stopwatch sw;
        sw.start();
        normalizationParallelSections(uCopy);
        sw.stop();
        cout << "Parallel sections: " << sw.duration().count() << " ms, length " << computeVectorLength(uCopy) << endl;
    }

    {
        vector<double> uCopy = u;
        Stopwatch sw;
        sw.start();
        normalizationCriticalAndParallelFor(uCopy);
        sw.stop();
        cout << "Parallel for + critical section: " << sw.duration().count() << " ms, length " << computeVectorLength(uCopy) << endl;
    }

    {
        vector<double> uCopy = u;
        Stopwatch sw;
        sw.start();
        normalizationParallelForAndAtomic(uCopy);
        sw.stop();
        cout << "Parallel for + atomic update: " << sw.duration().count() << " ms, length " << computeVectorLength(uCopy) << endl;
    }

    {
        vector<double> uCopy = u;
        Stopwatch sw;
        sw.start();
        normalizationParallelSimd(uCopy);
        sw.stop();
        cout << "Parallel simd : " << sw.duration().count() << " ms, length " << computeVectorLength(uCopy) << endl;
    }

    {
        vector<double> uCopy = u;
        Stopwatch sw;
        sw.start();
        normalizationParallelForAndReduction(uCopy);
        sw.stop();
        cout << "Parallel for + reduction: " << sw.duration().count() << " ms, length " << computeVectorLength(uCopy) << endl;
    }

    return 0;
}
