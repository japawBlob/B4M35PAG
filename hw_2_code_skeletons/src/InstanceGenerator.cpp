#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <stdint.h>

using namespace std;

constexpr float pi = 3.141592653589f;

// Taken from Wikipedia: https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain
// Implementation of Andrew's monotone chain 2D convex hull algorithm.
// Asymptotic complexity: O(n log n).
// Practical performance: 0.5-1.0 seconds for n=1000000 on a 1GHz machine.

struct Point {
	Point() : x(0.0), y(0.0) {}

	Point(float xa, float ya) : x(xa), y(ya) {}

	bool operator<(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}

	float x, y;
};

// 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
// Returns a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
float cross(const Point &O, const Point &A, const Point &B) {
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<Point> convex_hull(vector<Point> P) {
	int n = P.size(), k = 0;
	vector<Point> H(2 * n);

	// Sort points lexicographically
	sort(P.begin(), P.end());

	// Build lower hull
	for (int i = 0; i < n; ++i) {
		while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0) {
			k--;
		}
		H[k++] = P[i];
	}

	// Build upper hull
	for (int i = n - 2, t = k + 1; i >= 0; i--) {
		while (k >= t && cross(H[k - 2], H[k - 1], P[i]) <= 0) {
			k--;
		}
		H[k++] = P[i];
	}

	H.resize(k - 1);
	return H;
}

int main(int argc, char *argv[]) {
	int32_t n;
	string outputFile;

	if (argc != 3) {
		cout << "Instance generator for triangulation homework assignment." << endl;
		cout << endl << "Usage:" << endl;
		cout << "\t" << argv[0] << " NUM_POINTS INSTANCE_PATH" << endl;
		return 1;
	}
	else {
		n = atoi(argv[1]);
		outputFile = argv[2];
	}


	random_device rd;
	default_random_engine gen(rd());
	uniform_real_distribution<float> rot(0.0f, 2 * pi);
	uniform_real_distribution<float> prolong(0.0f, 0.03f);
	uniform_real_distribution<float> axisLength(0.5f, 2.0f);

	vector<Point> genPoints;
	float phi = 0.0;
	float rotation = rot(gen);
	float a = axisLength(gen), b = axisLength(gen);
	while (genPoints.size() < n) {
		phi = rot(gen);
		double p = prolong(gen);
		double x = a * cos(phi) * (1.0 + p);
		double y = b * sin(phi) * (1.0 + p);
		x = x * cos(rotation) - y * sin(rotation) + 2.0;
		y = x * sin(rotation) + y * cos(rotation) + 2.0;
		genPoints.emplace_back(x, y);
	}

	// Select convex hull...
	genPoints = convex_hull(genPoints);
	int32_t numPoints = genPoints.size();

	ofstream bout(outputFile.c_str(), ofstream::binary | ofstream::trunc);
	if (bout) {
		bout.write((char *) &numPoints, sizeof(int32_t));
		for (const Point &p : genPoints) {
			bout.write((char *) &p.x, sizeof(float));
			bout.write((char *) &p.y, sizeof(float));
		}
		bout.close();
	} else {
		cerr << "Cannot write to file '" << outputFile << "'!" << endl;
	}

	cout << "In total " << genPoints.size() << " points generated..." << endl;

	return 0;
}

