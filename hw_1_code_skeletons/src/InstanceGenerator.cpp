#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <stdint.h>

using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 3) {
		cout << "Instance generator for LU decomposition homework assignment." << endl;
		cout << endl << "Usage:" << endl;
		cout << "\t" << argv[0] << " MATRIX_SIZE INSTANCE_PATH" << endl;
		return 1;
	}

	uint64_t n = atoi(argv[1]);
	string matrixFile = argv[2];

	random_device rd;
	default_random_engine gen(rd());
	uniform_real_distribution<double> val(1.0, 10.0);
	vector<vector<double>> A(n, vector<double>(n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			A[i][j] = val(gen);
		}
	}

	ofstream bout(matrixFile.c_str(), ofstream::out | ofstream::binary | ofstream::trunc);
	if (bout.fail()) {
		cerr << "Cannot write to '" << matrixFile << "' file!" << endl;
		return 1;
	}

    bout.write((char *) &n, sizeof(uint64_t));
    for (uint64_t r = 0; r < n; ++r) {
        bout.write((char *) A[r].data(), n * sizeof(double));
    }

	return 0;
}

