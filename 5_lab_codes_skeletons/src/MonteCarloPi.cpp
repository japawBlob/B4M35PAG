#include <random>
#include <algorithm>
#include <iostream>
#include <vector>
#include <omp.h>
#include <cmath>

using namespace std;

// Do in parallel.
int fnNumSamplesInCircle(int randomSeed, int numSamples) {
    mt19937 randomEngine(randomSeed);
    uniform_real_distribution<float> dist(-1.0, 1.0);

    int numSamplesInCircle = 0;
    for (int i = 0; i < numSamples; ++i) {
        auto x = dist(randomEngine);
        auto y = dist(randomEngine);
        if(sqrt(pow(x,2)+pow(y,2))<1){
            numSamplesInCircle++;
        }
    }

    return numSamplesInCircle;
}

int main() {
    int totalNumSamples = 100000000;

    int numIterations = 100;
    int numSamplesPerIteration = totalNumSamples / numIterations;
    if ((totalNumSamples % numIterations) != 0) {
        cout << "Total number of samples must be multiple of number of iterations!" << endl;
        exit(1);
    }

    int numSamplesInCircle = 0;

    numSamplesInCircle = fnNumSamplesInCircle(0xAA791D,totalNumSamples);

    cout << (4.0 * numSamplesInCircle) / (1.0 * totalNumSamples) << endl;
    return 0;
}
