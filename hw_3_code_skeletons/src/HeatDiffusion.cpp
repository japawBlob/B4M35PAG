#include <mpi.h>
#include <chrono>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <tuple>
#include <iostream>

using namespace std;
using namespace std::chrono;

// Spot with permanent temperature on coordinates [x,y].
struct Spot {
    int mX;
    int mY;
    float mTemperature;



    bool operator==(const Spot &b) const {
        return (mX == b.mX) && (mY == b.mY);
    }
};

tuple<int, int, vector<Spot>> readInstance(string instanceFileName) {
    int width, height;
    vector<Spot> spots;
    string line;

    ifstream file(instanceFileName);
    if (file.is_open()) {
        int lineId = 0;
        while (std::getline(file, line)) {
            stringstream ss(line);
            if (lineId == 0) {
                ss >> width;
            } else if (lineId == 1) {
                ss >> height;
            } else {
                int i, j, temperature;
                ss >> i >> j >> temperature;
                spots.push_back({i, j, (float)temperature});
            }
            lineId++;
        }
        file.close();
    } else {
        throw runtime_error("It is not possible to open instance file!\n");
    }
    return make_tuple(width, height, spots);
}

void writeOutput(
        const int myRank,
        const int width,
        const int height,
        const string outputFileName,
        const vector<float> &temperatures) {
    // Draw the output image in Netpbm format.
    ofstream file(outputFileName);
    if (file.is_open()) {
        if (myRank == 0) {
            file << "P2\n" << width << "\n" << height << "\n" << 255 << "\n";
            for (auto temperature: temperatures) {
                file << (int)max(min(temperature, 255.0f), 0.0f) << " ";
            }
        }
    }
}

void printHelpPage(char *program) {
    cout << "Simulates a simple heat diffusion." << endl;
    cout << endl << "Usage:" << endl;
    cout << "\t" << program << " INPUT_PATH OUTPUT_PATH" << endl << endl;
}

int main(int argc, char **argv) {
    // Initialize MPI
    //MPI_Init(&argc, &argv);
    //int worldSize, myRank;
    //MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
    //MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    //cout << "My rank: " << myRank << endl;

    if (argc == 1) {
        //if (myRank == 0) {
            printHelpPage(argv[0]);
        //}
        //MPI_Finalize();
        exit(0);
    } else if (argc != 3) {
        //if (myRank == 0) {
            printHelpPage(argv[0]);
        //}
        //MPI_Finalize();
        exit(1);
    }

    // Read the input instance.
    int width, height;  // Width and height of the matrix.
    vector<Spot> spots; // Spots with permanent temperature.
    //if (myRank == 0) {
        tie(width, height, spots) = readInstance(argv[1]);
    //}
    //if(myRank == 0) {
        high_resolution_clock::time_point start = high_resolution_clock::now();


        //-----------------------\\
    // Insert your code here \\
    //        |  |  |        \\
    //        V  V  V        \\
    // TODO: Fill this array on processor with rank 0. It must have height * width elements and it contains the
        // linearized matrix of temperatures in row-major order
        // (see https://en.wikipedia.org/wiki/Row-_and_column-major_order)
        vector<vector<float>> temp(height, vector<float>(width, 128));
        vector<vector<float>> blobMatrix(height, vector<float>(width, 128));
        vector<vector<bool>> permaSpots(height, vector<bool>(width, false));

        for (auto blob: spots) {
            temp[blob.mY][blob.mX] = blob.mTemperature;
            permaSpots[blob.mY][blob.mX] = true;
            std::cout << "x: " << blob.mX << "  | y: " << blob.mY << "  | temperature: " << blob.mTemperature
                      << std::endl;
        }

        bool continueComputation = false;
        const float limite = 0.00001f;

        /*for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                std::cout << temp[i][j] << " ";
                //temperatures.push_back(temp[i][j]);
            }
            std::cout << std::endl;
        }*/

        do {
            bool checkForContinue = true;
            continueComputation = false;

            int i = 0, j = 0;

            //roh v levo nahore
            blobMatrix[i][j] = temp[i][j];
            temp[i][j] = (temp[i][j] + temp[i][j + 1] + temp[i + 1][j] + temp[i + 1][j + 1]) / 4;
            if (/*checkForContinue && */abs(blobMatrix[i][j] - temp[i][j]) > limite) {
                bool skip = false;
                for (auto blob: spots) {
                    if (i == blob.mY && j == blob.mX) {
                        temp[i][j] = blob.mTemperature;
                        skip = true;
                    }
                }
                if (!skip) {
                    //std::cout << "1)      x: " << j << "  | y: " << i << "  | delta: " << abs(blobMatrix[i][j] - temp[i][j]) << std::endl;
                    continueComputation = true;
                    checkForContinue = false;
                }
            }

            //prvni radek
            for (j = 1; j < width - 1; ++j) {
                blobMatrix[i][j] = temp[i][j];
                temp[i][j] = (blobMatrix[i][j - 1] + temp[i][j] + temp[i][j + 1] + temp[i + 1][j - 1] + temp[i + 1][j] +
                              temp[i + 1][j + 1]) / 6;
                if (/*checkForContinue &&*/ (abs(blobMatrix[i][j] - temp[i][j]) > limite)) {
                    bool skip = false;
                    for (auto blob: spots) {
                        if (i == blob.mY && j == blob.mX) {
                            temp[i][j] = blob.mTemperature;
                            skip = true;
                        }
                    }
                    if (!skip) {
                        //std::cout << "2)      x: " << j << "  | y: " << i << "  | delta: " << abs(blobMatrix[i][j] - temp[i][j]) << std::endl;
                        continueComputation = true;
                        checkForContinue = false;
                    }
                }
            }

            //roh v pravo nahore
            blobMatrix[i][j] = temp[i][j];
            temp[i][j] = (blobMatrix[i][j - 1] + temp[i][j] + temp[i+1][j] + temp[i + 1][j - 1]) / 4;
            if (/*checkForContinue && */(abs(blobMatrix[i][j] - temp[i][j]) > limite)) {
                bool skip = false;
                for (auto blob: spots) {
                    if (i == blob.mY && j == blob.mX) {
                        temp[i][j] = blob.mTemperature;
                        skip = true;
                    }
                }
                if (!skip) {
                    //std::cout << "3)      x: " << j << "  | y: " << i << "  | delta: " << abs(blobMatrix[i][j] - temp[i][j]) << std::endl;
                    continueComputation = true;
                    checkForContinue = false;
                }
            }
            //hlavni cast matice
            for (i = 1; i < height - 1; ++i) {
                j = 0;
                //levy kraj
                blobMatrix[i][j] = temp[i][j];
                temp[i][j] =
                        (blobMatrix[i - 1][j] + blobMatrix[i - 1][j + 1] + temp[i][j] + temp[i][j + 1] +
                         temp[i + 1][j] +
                         temp[i + 1][j + 1]) / 6;
                if (/*checkForContinue && */(abs(blobMatrix[i][j] - temp[i][j]) > limite)) {
                    bool skip = false;
                    for (auto blob: spots) {
                        if (i == blob.mY && j == blob.mX) {
                            temp[i][j] = blob.mTemperature;
                            skip = true;
                        }
                    }
                    if (!skip) {
                        //std::cout << "4)      x: " << j << "  | y: " << i << "  | delta: " << abs(blobMatrix[i][j] - temp[i][j]) << std::endl;
                        continueComputation = true;
                        checkForContinue = false;
                    }
                }
                //radek
                for (j = 1; j < width - 1; ++j) {
                    blobMatrix[i][j] = temp[i][j];
                    temp[i][j] = (blobMatrix[i - 1][j - 1] + blobMatrix[i - 1][j] + blobMatrix[i - 1][j + 1] +
                                  blobMatrix[i][j - 1] + temp[i][j] + temp[i][j + 1] + temp[i + 1][j - 1] +
                                  temp[i + 1][j] +
                                  temp[i + 1][j + 1]) / 9;
                    //temperatures.push_back(temp[i][j]);

                    if (/*checkForContinue && */(abs(blobMatrix[i][j] - temp[i][j]) > limite)) {
                        bool skip = false;
                        for (auto blob: spots) {
                            //std::cout << "5) j: " << j << "  | i: " << i << "  | x: " << blob.mX << "  | y: " << blob.mY << std::endl;
                            if (i == blob.mY && j == blob.mX) {
                                temp[i][j] = blob.mTemperature;
                                skip = true;
                                break;
                            }
                        }
                        if (!skip) {
                            //std::cout << "5)      x: " << j << "  | y: " << i << "  | delta: " << abs(blobMatrix[i][j] - temp[i][j]) << "  | temp: " << blobMatrix[i][j] << std::endl;
                            continueComputation = true;
                            checkForContinue = false;
                        }
                    }
                }
                // pravy kraj radku
                blobMatrix[i][j] = temp[i][j];
                temp[i][j] = (blobMatrix[i - 1][j - 1] + blobMatrix[i - 1][j] + blobMatrix[i][j - 1] + temp[i][j] +
                              temp[i + 1][j - 1] + temp[i + 1][j]) / 6;
                if (/*checkForContinue && */(abs(blobMatrix[i][j] - temp[i][j]) > limite)) {
                    bool skip = false;
                    for (auto blob: spots) {
                        if (i == blob.mY && j == blob.mX) {
                            temp[i][j] = blob.mTemperature;
                            skip = true;
                        }
                    }
                    if (!skip) {
                        //std::cout << "6)      x: " << j << "  | y: " << i << "  | delta: " << abs(blobMatrix[i][j] - temp[i][j]) << std::endl;
                        continueComputation = true;
                        checkForContinue = false;
                    }
                }
            }
            //levy dolni roh
            j = 0;
            blobMatrix[i][j] = temp[i][j];
            temp[i][j] = (blobMatrix[i - 1][j] + blobMatrix[i - 1][j + 1] + temp[i][j] + temp[i][j + 1]) / 4;
            if (/*checkForContinue && */(abs(blobMatrix[i][j] - temp[i][j]) > limite)) {
                bool skip = false;
                for (auto blob: spots) {
                    if (i == blob.mY && j == blob.mX) {
                        temp[i][j] = blob.mTemperature;
                        skip = true;
                    }
                }
                if (!skip) {
                    //std::cout << "7)      x: " << j << "  | y: " << i << "  | delta: " << abs(blobMatrix[i][j] - temp[i][j]) << std::endl;
                    continueComputation = true;
                    checkForContinue = false;
                }
            }
            //posledni radek
            for (j = 1; j < width - 1; ++j) {
                blobMatrix[i][j] = temp[i][j];
                temp[i][j] =
                        (blobMatrix[i - 1][j - 1] + blobMatrix[i - 1][j] + blobMatrix[i - 1][j + 1] +
                         blobMatrix[i][j - 1] +
                         temp[i][j] + temp[i][j + 1]) / 6;
                //temperatures.push_back(temp[i][j]);

                if (/*checkForContinue && */(abs(blobMatrix[i][j] - temp[i][j]) > limite)) {
                    bool skip = false;
                    for (auto blob: spots) {
                        if (i == blob.mY && j == blob.mX) {
                            temp[i][j] = blob.mTemperature;
                            skip = true;
                        }
                    }
                    if (!skip) {
                        //std::cout << "8)      x: " << j << "  | y: " << i << "  | delta: " << abs(blobMatrix[i][j] - temp[i][j]) << std::endl;
                        continueComputation = true;
                        checkForContinue = false;
                    }
                }
            }
            // pravy dolni roh
            blobMatrix[i][j] = temp[i][j];
            temp[i][j] = (blobMatrix[i - 1][j - 1] + blobMatrix[i - 1][j] + blobMatrix[i][j - 1] + temp[i][j]) / 4;
            if (/*checkForContinue && */(abs(blobMatrix[i][j] - temp[i][j]) > limite)) {
                bool skip = false;
                for (auto blob: spots) {
                    if (i == blob.mY && j == blob.mX) {
                        temp[i][j] = blob.mTemperature;
                        skip = true;
                    }
                }
                if (!skip) {
                    //std::cout << "9)      x: " << j << "  | y: " << i << "  | delta: " << abs(blobMatrix[i][j] - temp[i][j]) << std::endl;
                    continueComputation = true;
                    checkForContinue = false;
                }
            }

            for (auto blob: spots) {
                temp[blob.mY][blob.mX] = blob.mTemperature;
                blobMatrix[blob.mY][blob.mX] = blob.mTemperature;
            }
        } while (continueComputation);


        vector<float> temperatures(width * height, 0);

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                temperatures[(height) * i + j] = temp[i][j];
                //temperatures.push_back(temp[i][j]);
            }
        }





        //-----------------------\\


        double totalDuration = duration_cast<duration<double>>(high_resolution_clock::now() - start).count();
        cout << "computational time: " << totalDuration << " s" << endl;

        //if (myRank == 0) {
            string outputFileName(argv[2]);
            writeOutput(0, width, height, outputFileName, temperatures);
        //}
    //}
    //MPI_Finalize();
    exit(0);
    return 0;
}

