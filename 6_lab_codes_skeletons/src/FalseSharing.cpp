#include <iostream>
#include <vector>
#include <omp.h>

#include "Utils.hpp"

using namespace std;

double withFalseSharing(int numIterations) {
    double x = 0.0;
    double y = 0.0;
    #pragma omp parallel num_threads(2)
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                for (int i = 0; i < numIterations; i++) {
                    x += sin(i) * cos(i);
                }
            }

            #pragma omp section
            {
                for (int i = 0; i < numIterations; i++) {
                    y += sin(i) * cos(i);
                }
            }
        }
    }

    return x + y;
}

double noFalseSharing(int numIterations) {
    double x = 0.0;
    double y = 0.0;
    #pragma omp parallel num_threads(2)
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                double privateResult = 0.0;
                for (int i = 0; i < numIterations; i++) {
                    privateResult += sin(i) * cos(i);
                }
                x = privateResult;
            }

            #pragma omp section
            {
                double privateResult = 0.0;
                for (int i = 0; i < numIterations; i++) {
                    privateResult += sin(i) * cos(i);
                }
                y = privateResult;
            }
        }
    }

    return x + y;
}

int main() {
    int numIterations = 50000000;

    {
        Stopwatch sw;
        sw.start();
        auto result = withFalseSharing(numIterations);
        sw.stop();
        cout << "withFalseSharing: " << sw.duration().count() << " ms, result " << result << endl;
    }

    {
        Stopwatch sw;
        sw.start();
        auto result = noFalseSharing(numIterations);
        sw.stop();
        cout << "noFalseSharing: " << sw.duration().count() << " ms, result " << result << endl;
    }

    return 0;
}
