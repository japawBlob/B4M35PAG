#include <random>
#include <fstream>
#include <vector>
#include <string>

#include "Utils.h"

using namespace std;

// Generates the records completely on random.
vector<vector<int>> randomRecords(mt19937 randGen, int numRecords, int maxRecordLen) {
    uniform_int_distribution<int> distRecordLen(1, maxRecordLen);
    uniform_int_distribution<int> distValues(1, 5);

    vector<vector<int>> records;
    for (auto i = 0; i < numRecords; i++) {
        auto recordLen = distRecordLen(randGen);
        vector<int> record;
        for (auto j = 0; j < recordLen; j++) {
            record.push_back(distValues(randGen));
        }
        records.push_back(record);
    }

    return records;
}

int main(int argc, char *argv[]) {
    int numRecords = stoi(argv[1]);
    int maxRecordLen = stoi(argv[2]);
    string filePath = argv[3];

    random_device randomDevice;
    mt19937 randGen(randomDevice());

    auto records = randomRecords(randGen, numRecords, maxRecordLen);
    writeRecords(records, filePath);
}
