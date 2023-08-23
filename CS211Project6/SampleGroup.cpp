/*
 * TODO: Add file name, author, date, purpose
 */

#include "sampleGroup.h"

using namespace std; // Debatable, but easier for now.

SampleGroup::SampleGroup() {
    nAllocated = 10;
    nSamples = 0;
    samples = new Sample*[nAllocated];
    xRange[0] = 0.0;
    xRange[1] = 0.0;
    yRange[0] = 0.0;
    yRange[1] = 0.0;
}

SampleGroup::SampleGroup(int initialCapacity) {
    nAllocated = initialCapacity;
    nSamples = 0;
    samples = new Sample*[nAllocated];
    xRange[0] = 0.0;
    xRange[1] = 0.0;
    yRange[0] = 0.0;
    yRange[1] = 0.0;
}

SampleGroup::~SampleGroup() {
    for (int i = 0; i < nSamples; i++) {
        delete samples[i];
    }
    delete[] samples;
}

int SampleGroup::getNumberOfSamples() const {
    return nSamples;
}

bool SampleGroup::addSample(const Sample& sample) {
    if (nSamples >= nAllocated) {
        int newCapacity = nAllocated * 2;
        Sample** newSamples = new Sample*[newCapacity];

        for (int i = 0; i < nSamples; i++) {
            newSamples[i] = samples[i];
        }

        delete[] samples;
        samples = newSamples;
        nAllocated = newCapacity;
    }

    samples[nSamples] = new Sample(sample);
    nSamples++;
    return true;
}

bool SampleGroup::addSample(Sample* samplePtr) {
    if (nSamples >= nAllocated) {
        int newCapacity = nAllocated * 2;
        Sample** newSamples = new Sample*[newCapacity];

        for (int i = 0; i < nSamples; i++) {
            newSamples[i] = samples[i];
        }

        delete[] samples;
        samples = newSamples;
        nAllocated = newCapacity;
    }

    samples[nSamples] = samplePtr;
    nSamples++;
    return true;
}

bool SampleGroup::isWithinBounds(const Sample& sample) const {
    double x = sample.getX();
    double y = sample.getY();

    // Check if the sample's coordinates are within the xRange and yRange
    if (x < xRange[0] || x > xRange[1]) {
        return false;
    }

    if (y < yRange[0] || y > yRange[1]) {
        return false;
    }

    return true;
}

void SampleGroup::printStats(ostream& outStream) const {
    outStream << "SampleGroup has " << nSamples << " stored out of " << nAllocated << " available.\n";
    outStream << "Average: " << average << "\n";
    outStream << "X Range: [" << xRange[0] << ", " << xRange[1] << "]\n";
    outStream << "Y Range: [" << yRange[0] << ", " << yRange[1] << "]\n";
    outStream << "Data Range: [" << dataRange[0] << ", " << dataRange[1] << "]\n";
}

void SampleGroup::printAll(ostream& outStream) const {
    printStats(outStream);

    for (int i = 0; i < nSamples; i++) {
        outStream << *samples[i] << "\n";
    }
}

Sample* SampleGroup::getSampleByID(int id) const {
    for (int i = 0; i < nSamples; i++) {
        if (samples[i]->getID() == id) {
            return samples[i];
        }
    }
    return nullptr;
}

// Getter method for xRange
const double* SampleGroup::getXRange() const {
    return xRange;
}

// Getter method for yRange
const double* SampleGroup::getYRange() const {
    return yRange;
}

void SampleGroup::calculateBounds() {
    if (nSamples == 0) {
        // No samples in the group, set bounds to default values
        xRange[0] = 0.0;
        xRange[1] = 0.0;
        yRange[0] = 0.0;
        yRange[1] = 0.0;
        dataRange[0] = 0.0;
        dataRange[1] = 0.0;
    } else {
        // Initialize the bounds with the first sample in the group
        double xMin = samples[0]->getX();
        double xMax = samples[0]->getX();
        double yMin = samples[0]->getY();
        double yMax = samples[0]->getY();
        double dataMin = samples[0]->getData();
        double dataMax = samples[0]->getData();

        // Find the minimum and maximum values for x, y, and data
        for (int i = 1; i < nSamples; i++) {
            double x = samples[i]->getX();
            double y = samples[i]->getY();
            double data = samples[i]->getData();

            if (x < xMin) {
                xMin = x;
            }
            if (x > xMax) {
                xMax = x;
            }
            if (y < yMin) {
                yMin = y;
            }
            if (y > yMax) {
                yMax = y;
            }
            if (data < dataMin) {
                dataMin = data;
            }
            if (data > dataMax) {
                dataMax = data;
            }
        }

        // Update the bounds
        xRange[0] = xMin;
        xRange[1] = xMax;
        yRange[0] = yMin;
        yRange[1] = yMax;
        dataRange[0] = dataMin;
        dataRange[1] = dataMax;
    }
}

