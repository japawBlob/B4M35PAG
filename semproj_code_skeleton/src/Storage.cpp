#include <vector>
#include <algorithm>
#include "Utils.h"
#include "queue"
#include "omp.h"
#include <limits.h>

using namespace std;

struct graphNode {
    bool isConnected;
    int name;
    int minEdge;
    int parent;
};
struct edge{
    int cost;
    int from;
    int to;
    bool operator<(const edge& rhs) const
    {
        return -cost < -rhs.cost;
    }
};

int levensteinDist(const vector<int> & w1, const vector<int> & w2){
    int size_i = w1.size()+1;
    int size_j = w2.size()+1;

    int D [size_i][size_j];
    for (int i = 0; i < size_i; ++i) {
        D[i][0] = i;
    }
    for (int j = 0; j < size_j; ++j) {
        D[0][j] = j;
    }

    for (int i = 1; i < size_i; ++i) {
        for (int j = 1; j < size_j; ++j) {
            if(w1[i-1] == w2[j-1]){
                D[i][j] = D[i-1][j-1];
            } else {
                D[i][j] = 1 + std::min(D[i-1][j-1],std::min(D[i-1][j],D[i][j-1]));
            }
        }
    }
//    for (int i = 0; i < size_i; ++i) {
//        for (int j = 0; j < size_j; ++j) {
//            cout << D[i][j] << " ";
//        }
//        cout << endl;
//    }
    return D[size_i-1][size_j-1];
}
//Memory efficient levenshtein
int LevenshteinDistance(const vector<int> &source, const vector<int> &target) {
    if (source.size() > target.size()) {
        return LevenshteinDistance(target, source);
    }
    const int min_size = source.size(), max_size = target.size();
    std::vector<int> lev_dist(min_size + 1);

    for (int i = 0; i <= min_size; ++i) {
        lev_dist[i] = i;
    }

    for (int j = 1; j <= max_size; ++j) {
        int previous_diagonal = lev_dist[0], previous_diagonal_save;
        lev_dist[0]++;

        for (int i = 1; i <= min_size; ++i) {
            previous_diagonal_save = lev_dist[i];
            if (source[i - 1] == target[j - 1]) {
                lev_dist[i] = previous_diagonal;
            } else {
                lev_dist[i] = std::min(std::min(lev_dist[i - 1], lev_dist[i]), previous_diagonal) + 1;
            }
            previous_diagonal = previous_diagonal_save;
        }
    }
    return lev_dist[min_size];
}

int levensteinDist(vector<int> w1, vector<int> w2, int ** D){
    int size_i = w1.size()+1;
    int size_j = w2.size()+1;

    for (int i = 1; i < size_i; ++i) {
        //#pragma omp simd
        for (int j = 1; j < size_j; ++j) {
            if(w1[i-1] == w2[j-1]){
                D[i][j] = D[i-1][j-1];
            } else {
                D[i][j] = 1 + std::min(D[i-1][j-1],std::min(D[i-1][j],D[i][j-1]));
            }
        }
    }
//    for (int i = 0; i < size_i; ++i) {
//        for (int j = 0; j < size_j; ++j) {
//            cout << D[i][j] << " ";
//        }
//        cout << endl;
//    }
    return D[size_i-1][size_j-1];
}


int ** graph;

//Stolen from geeksforgeeks.org https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/
void printMST(int parent[], int numberOfRecords, int ** graph)
{
    printf("Edge   Weight\n");
    for (int i = 1; i < numberOfRecords; i++)
        printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
}

pair<int,int> findMinimalEdge(const vector<graphNode> & graphNodes) {
    int min = INT_MAX;
    int index = -1;
    unsigned numberOfRecords = graphNodes.size();
#pragma omp parallel
    {
        int localIndex = index;
        int localMin = min;
#pragma omp for
        for (int i = 0; i < numberOfRecords; i++) {
            if (!graphNodes[i].isConnected && graphNodes[i].minEdge < localMin) {
                localMin = graphNodes[i].minEdge;
                localIndex = i;
            }
        }
#pragma omp critical
        {
            if (localMin < min) {
                min = localMin;
                index = localIndex;
            }
        }
    }
    return make_pair(index,min);
}

int primParallel(const unsigned numberOfRecords){
    vector<graphNode> graphNodes (numberOfRecords, {false,0,INT_MAX,-1});
    for (int i = 0; i < numberOfRecords; i++){
        graphNodes[i].name = i;
    }
    int totalCost = 0;
    graphNodes[0].minEdge = 0;

    for (int i = 0; i < numberOfRecords; i++){
        pair<int,int> blob = findMinimalEdge(graphNodes);
        int currentNode = blob.first;
        totalCost += blob.second;
        graphNodes[currentNode].isConnected = true;

#pragma omp parallel for schedule(static)
        for (int j = 0; j < numberOfRecords; j++) {
            if (!graphNodes[j].isConnected && graph[currentNode][j] < graphNodes[j].minEdge)
                graphNodes[j].parent = currentNode, graphNodes[j].minEdge = graph[currentNode][j];
        }
    }
    return totalCost;
}

int main(int argc, char *argv[]) {
    auto programArguments = ProgramArguments::Parse(argc, argv);

    // The input records, e.g., records[0] is the first record in the input file.
    vector<vector<int>> records = readRecords(programArguments.mInputFilePath);

    //printRecords(records);

    const unsigned numberOfRecords = records.size();
    graph = new int*[numberOfRecords];
    for (int i = 0; i < numberOfRecords; ++i) {
        graph[i] = new int[numberOfRecords];
    }
    //auto timer = Stopwatch();
    //auto timer1 = Stopwatch();

    /*vector<int> blob1 = records[1];
    vector<int> blob2 = records[8];*/

    //timer.start();
    //timer1.start();
    //cout << timer1.duration().count() << "ms\n";

    #pragma omp parallel shared(graph, records)
    {
        #pragma omp for schedule(dynamic)
        for (int i = 0; i < numberOfRecords; ++i) {
            //if(i%1000 == 0) cout << i << " " << timer1.duration().count() << "ms\n";
            graph[i][i] = 0;
            vector<int> record = records[i];
            for (int j = i + 1; j < numberOfRecords; ++j) {
                int dist = LevenshteinDistance(record, records[j]);
                //int dist = levensteinDist(record, records[j]);
                /*std::string sw1;
                for (auto blob : records[i]) {
                    sw1 += static_cast<char>(blob+48);
                }
                std::string sw2;
                for (auto blob : records[j]) {
                    sw2 += static_cast<char>(blob+48);
                }
                std::cout << "Dist of w1: " << sw1 << " and w2: " << sw2 << "\nis: " << dist << "\n";*/
                graph[i][j] = dist;
                graph[j][i] = dist;
            }
        }
    }
    //timer1.stop();
    //cout << "time for levensthein: " << timer1.duration().count() << "ms\n";

    /*for(int i = 0; i<numberOfRecords; i++){
        for(int j = 0; j<numberOfRecords; j++){
            printf("%d,", graph[i][j]);
        }
        printf("\n");
    }*/
    /*printRecords(records);
    cout << "----\n";
    for (int i = 0; i < numberOfRecords; ++i) {
        for (int j = 0; j < numberOfRecords; ++j) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }*/
/*    auto timer2 = Stopwatch();
    timer2.start();
    priority_queue<edge> prioQueue;
    int from [numberOfRecords];
    unsigned numberOfConnectedNodes = 0;
    for (int i = 1; i < numberOfRecords; ++i) {
        edge blob;
        blob.cost = graph[0][i];
        blob.from = 0;
        blob.to = i;
        prioQueue.push(blob);
    }
    graphNodes[0].isConnected = true;
    numberOfConnectedNodes++;
    int treeCost = 0;
    while (numberOfConnectedNodes < numberOfRecords) {
        edge currentEdge = prioQueue.top();
        prioQueue.pop();
        if(graphNodes[currentEdge.to].isConnected){
            continue;
        }
        treeCost += currentEdge.cost;
        graphNodes[currentEdge.to].isConnected = true;
        from[currentEdge.to] = currentEdge.from;
        numberOfConnectedNodes++;
        for (int i = 0; i < numberOfRecords; ++i) {
            if(graphNodes[i].isConnected) continue;
            edge blob = {
                    graph[currentEdge.to][i],
                    currentEdge.to,
                    i,
            };
            prioQueue.push(blob);
        }
    }*/
    //printMST(from,numberOfRecords,graph);
    /*int treeCost = 0;
    for (int i = 1; i < numberOfRecords; i++)
        treeCost += graph[i][from[i]];
    cout << treeCost <<" time for minimum spanning tree seq: " << timer2.duration().count() << "ms\n";*/
    //auto timer2 = Stopwatch();
    //timer2.start();
    int blobTreeCost = primParallel(numberOfRecords);
    //timer2.stop();
    //cout << "time for minimum spanning tree par: " << timer2.duration().count() << "ms\n";


    // TODO: fill the treeCost variable with the MST of the records' edit distances graph.
    //timer.stop();

    //cout << blobTreeCost << " time: " << timer.duration().count() << endl;
    writeCost(blobTreeCost, programArguments.mOutputFilePath);
    for (int i = 0; i < numberOfRecords; ++i) {
        delete [] graph[i];
    }
    delete [] graph;
}
