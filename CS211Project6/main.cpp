/* Name Abeer Ismail
 * Date 6/4/2023
 * CS 211 Project 6
 * Using inheritance, multiple files, and a analyzedset class to analyzed samples
*/
#include <iostream>
#include <fstream>
#include <string>
#include "sample.h"
#include "sampleGroup.h"
#include "analyzedSet.h"

using namespace std;

int main(int argc, char** argv) {
    bool debugMode = false;
    string filename;

    if (argc > 1) {
        string arg = argv[1];
        if (arg == "-d") {
            debugMode = true;
        } else {
            filename = arg;
        }
    }


    SampleGroup allSamples;
    AnalyzedSet analyzedSet;

    // Read and process input data
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        // Read the first section of samples
        double x, y, data;
        while (inputFile >> x >> y >> data && data >= -1000.0) {
            Sample sample(x, y, data);
            allSamples.addSample(sample);
        }

        // Read the sets of sample indices
        int sampleIndex;
        while (inputFile >> sampleIndex && sampleIndex >= 0) {
            Sample* samplePtr = allSamples.getSampleByID(sampleIndex);
            if (samplePtr != nullptr) {
                analyzedSet.addSample(samplePtr);
            } else {
                cout << "Error: Invalid sample ID " << sampleIndex << endl;
            }
        }

        // Calculate bounds and averages
        allSamples.calculateBounds();
        analyzedSet.calculateBounds();

        // Read the second section of samples
        while (inputFile >> x >> y >> data && data >= -1000.0) {
            Sample sample(x, y, data);
            bool isWithinAllSamples = allSamples.isWithinBounds(sample);
            bool isWithinAnalyzedSet = analyzedSet.isWithinBounds(sample);

            cout << "Sample: X=" << sample.getX() << ", Y=" << sample.getY() << ", Data=" << sample.getData() << endl;
            cout << "Is within All Samples: " << (isWithinAllSamples ? "Yes" : "No") << endl;
            cout << "Is within Analyzed Set: " << (isWithinAnalyzedSet ? "Yes" : "No") << endl;

            if (isWithinAnalyzedSet) {
                bool isOutlier = analyzedSet.isOutlier(sample);
                cout << "Is Outlier in Analyzed Set: " << (isOutlier ? "Yes" : "No") << endl;
            }

            cout << endl;
        }

        inputFile.close();
    } else {
        cout << "Error: Failed to open file " << filename << endl;
    }

    return 0;
}


