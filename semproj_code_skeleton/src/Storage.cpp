#include <vector>

#include "Utils.h"

using namespace std;

int main(int argc, char *argv[]) {
    auto programArguments = ProgramArguments::Parse(argc, argv);

    // The input records, e.g., records[0] is the first record in the input file.
    vector<vector<int>> records = readRecords(programArguments.mInputFilePath);

    // TODO: fill the treeCost variable with the MST of the records' edit distances graph.
    int treeCost = 0;

    cout << treeCost << endl;
    writeCost(treeCost, programArguments.mOutputFilePath);
}
