#include <iostream>
#include <vector>
#include <omp.h>
#include <cmath>

#include "Utils.hpp"

using namespace std;

double computeVectorLength(const vector<double> &u) {
    double sumSquares = 0;
    for (int i = 0; i < u.size(); i++) {
        sumSquares += u[i] * u[i];
    }

    return sqrt(sumSquares);
}

vector<double> normalizationSequential(vector<double> u) {
    double size = computeVectorLength(u);
    for (int i = 0; i < u.size(); ++i) {
        u[i] = u[i]/size;
    }
    return u;
}

vector<double> normalizationParallelSections(vector<double> u) {
    // TODO: work on vector u inplace
    return u;
}

vector<double> normalizationParallelForAndCritical(vector<double> u) {
    // TODO: work on vector u inplace
    return u;
}

vector<double> normalizationParallelForAndReduction(vector<double> u) {
    // TODO: work on vector u inplace
    return u;
}

int main() {
    vector<double> u = generateRandomVector(50000000);

    cout << "Length of the input vector: " << computeVectorLength(u) << endl;

    {
        Stopwatch sw;
        sw.start();
        auto uNorm = normalizationSequential(u);
        sw.stop();
        cout << "Sequential: " << sw.duration().count() << " ms, length " << computeVectorLength(uNorm) << endl;
    }

    {
        Stopwatch sw;
        sw.start();
        auto uNorm = normalizationParallelSections(u);
        sw.stop();
        cout << "Parallel sections: " << sw.duration().count() << " ms, length " << computeVectorLength(uNorm) << endl;
    }

    {
        Stopwatch sw;
        sw.start();
        auto uNorm = normalizationParallelForAndCritical(u);
        sw.stop();
        cout << "Parallel for + critical section: " << sw.duration().count() << " ms, length " << computeVectorLength(uNorm) << endl;
    }

    {
        Stopwatch sw;
        sw.start();
        auto uNorm = normalizationParallelForAndReduction(u);
        sw.stop();
        cout << "Parallel for + reduction: " << sw.duration().count() << " ms, length " << computeVectorLength(uNorm) << endl;
    }

    return 0;
}
