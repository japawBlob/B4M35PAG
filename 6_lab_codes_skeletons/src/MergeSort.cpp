#include <iostream>
#include <vector>
#include <omp.h>
#include <cmath>
#include <algorithm>

#include "Utils.hpp"

using namespace std;
template <typename Iterator>

void mergeSortSeqRecu(Iterator first, Iterator last)
{
    if (last - first > 1) {
        Iterator middle = first + (last - first) / 2;
        mergeSortSeqRecu(first, middle);
        mergeSortSeqRecu(middle, last);
        std::inplace_merge(first, middle, last);
    }
}

void mergeSortSequential(vector<double> &u) {
    mergeSortSeqRecu(u.begin(), u.end());
}
template <typename Iterator>
void mergeSortParRecu(Iterator first, Iterator last)
{
    if (last - first > 1) {
        Iterator middle = first + (last - first) / 2;
#pragma omp taskgroup
        {
#pragma omp task
            mergeSortParRecu(first, middle);
//#pragma omp task
            mergeSortParRecu(middle, last);
        }
        std::inplace_merge(first, middle, last);
    }
}
void mergeSortParallel(vector<double> &u) {
    #pragma omp parallel
    {
#pragma omp single
        mergeSortParRecu(u.begin(), u.end());
    }
}

int main() {
    vector<double> u = generateRandomVector(5000000);

    {
        auto uCopy = u;
        Stopwatch sw;
        sw.start();
        mergeSortSequential(uCopy);
        sw.stop();
        cout << "Sequential merge sort: " << sw.duration().count()
             << " ms, sorted correctly " << is_sorted(uCopy.begin(), uCopy.end()) << endl;
    }

    {
        auto uCopy = u;
        Stopwatch sw;
        sw.start();
        mergeSortParallel(uCopy);
        sw.stop();
        cout << "Parallel merge sort: " << sw.duration().count()
             << " ms, sorted correctly " << is_sorted(uCopy.begin(), uCopy.end()) << endl;
    }

    return 0;
}
