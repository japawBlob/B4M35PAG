#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    #pragma omp parallel for
    for (int i = 0; i < values.size(); i++) {
        values[i] *= 10;
    }

    int x = 0;

    #pragma omp parallel for reduction(+:x)
    for (int i = 0; i < values.size(); i++) {
        x += values[i];
    }

    // Has to be 550.
    cout << "Value of x: " << x << endl;

    return 0;
}
