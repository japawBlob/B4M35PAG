#include <random>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Stopwatch {
private:
    time_point<steady_clock> mStart;
    time_point<steady_clock> mEnd;
    bool mRunning;

public:
    Stopwatch() : mRunning(false) {}

    void start() {
        mStart = steady_clock::now();
        mRunning = true;
    }

    void stop() {
        mEnd = steady_clock::now();
        mRunning = false;
    }

    milliseconds duration() const {
        auto end = mRunning ? steady_clock::now() : mEnd;
        return duration_cast<milliseconds>(end - mStart);
    }
};

vector<double> generateRandomVector(int n, int seed = -1) {
    vector<double> u(n);

    random_device randomDevice;
    mt19937 randomEngine(seed == -1 ? randomDevice() : seed);

    uniform_real_distribution<double> distribution(1.0, 10.0);
    generate(u.begin(), u.end(), [&randomEngine, &distribution] { return distribution(randomEngine); });

    return u;
}

vector<vector<double>> generateRandomMatrix(int m, int n, int seed = -1) {
    random_device randomDevice;
    mt19937 randomEngine(seed == -1 ? randomDevice() : seed);

    vector<vector<double>> matrix;
    for (int i = 0; i < m; i++) {
        matrix.push_back(move(generateRandomVector(n, randomEngine())));
    }

    return matrix;
}

// Do not use this function in parallel vector normalization!
double computeVectorLength(const vector<double> &u) {
    double sumSquares = 0;
    for (int i = 0; i < u.size(); i++) {
        sumSquares += u[i] * u[i];
    }

    return sqrt(sumSquares);
}
