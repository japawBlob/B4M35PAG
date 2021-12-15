#ifndef STORAGE_UTILS_H
#define STORAGE_UTILS_H

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

void writeRecords(const vector<vector<int>> &records, string filePath) {
    ofstream bout(filePath.c_str(), ofstream::out | ofstream::binary | ofstream::trunc);

    int numRecords = records.size();
    bout.write((char *)&numRecords, sizeof(int));

    for (auto &record : records) {
        int recordLen = record.size();
        bout.write((char *)&recordLen, sizeof(int));
        bout.write((char *)record.data(), record.size() * sizeof(int));
    }
}

vector<vector<int>> readRecords(string filePath) {
    ifstream bin(filePath.c_str(), ifstream::in | ofstream::binary);

    int numRecords = 0;
    bin.read((char*)&numRecords, sizeof(int));

    vector<vector<int>> records;

    for (auto i = 0; i < numRecords; i++) {
        int recordLen = 0;
        bin.read((char*)&recordLen, sizeof(int));

        vector<int> record(recordLen, 0);
        bin.read((char*)record.data(), recordLen * sizeof(int));

        records.push_back(record);
    }

    return records;
}

void printRecords(const vector<vector<int>> &records) {
    for (auto &record : records) {
        for (auto &value : record) {
            cout << value << " ";
        }

        cout << endl;
    }
}

void writeCost(int cost, string filePath) {
    ofstream bout(filePath.c_str(), ofstream::out | ofstream::binary | ofstream::trunc);

    bout.write((char *)&cost, sizeof(int));
}

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

class ProgramArguments {
private:
    ProgramArguments(const string inputFilePath, const string outputFilePath)
        : mInputFilePath(inputFilePath), mOutputFilePath(outputFilePath)
    {

    }

public:
    string mInputFilePath;
    string mOutputFilePath;

    static ProgramArguments Parse(int argc, char *argv[]) {
        return ProgramArguments(argv[1], argv[2]);
    }
};

#endif
