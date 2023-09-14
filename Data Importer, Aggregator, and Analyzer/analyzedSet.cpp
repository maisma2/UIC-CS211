/*
 * Todo stuff
 */

#include "analyzedSet.h"
#include <math.h>

AnalyzedSet::AnalyzedSet() {
    dDataDx = 0;
    dDataDy = 0;
}

AnalyzedSet::AnalyzedSet(int initialCapacity) {
    dDataDx = 0;
    dDataDy = 0;
}

AnalyzedSet::~AnalyzedSet() {
}

bool AnalyzedSet::addSample(const Sample& sample) {
    Sample* sampleCopy = new Sample(sample);
    return addSample(sampleCopy);
}

bool AnalyzedSet::addSample(Sample* samplePtr) {
    if (isDuplicate(*samplePtr)) {
        return false;
    }

    bool addResult = SampleGroup::addSample(samplePtr);

    if (nSamples == 2 || samplePtr->getX() < getXRange()[0] || samplePtr->getX() > getXRange()[1]
        || samplePtr->getY() < getYRange()[0] || samplePtr->getY() > getYRange()[1]) {
        calculateSlopes();
    }


    return addResult;
}

void AnalyzedSet::calculateSlopes() {
    Sample* minXSample = findMinX();
    Sample* maxXSample = findMaxX();
    Sample* minYSample = findMinY();
    Sample* maxYSample = findMaxY();

    if (minXSample && maxXSample) {
        double dx = maxXSample->getX() - minXSample->getX();
        if (dx != 0) {
            dDataDx = (maxXSample->getData() - minXSample->getData()) / dx;
        }
        else {
            dDataDx = 0;
        }
    }

    if (minYSample && maxYSample) {
        double dy = maxYSample->getY() - minYSample->getY();
        if (dy != 0) {
            dDataDy = (maxYSample->getData() - minYSample->getData()) / dy;
        }
        else {
            dDataDy = 0;
        }
    }
}

bool AnalyzedSet::isDuplicate(const Sample& sample) const {
    return getSampleByID(sample.getID()) != nullptr;
}

bool AnalyzedSet::isOutlier(const Sample& sample) const {
    double data = sample.getData();

    // Check if the data value is outside the data range of the AnalyzedSet
    if (data < sample.getData() || data > sample.getData()) {
        return true;  // Data value is an outlier
    }

    // Calculate the average data value
    double sum = 0.0;
    for (int i = 0; i < nSamples; i++) {
        sum += samples[i]->getData();
    }
    double average = sum / nSamples;

    // Calculate the standard deviation of the data values
    double sumSquares = 0.0;
    for (int i = 0; i < nSamples; i++) {
        double diff = samples[i]->getData() - average;
        sumSquares += diff * diff;
    }
    double variance = sumSquares / nSamples;
    double standardDeviation = sqrt(variance);

    // Check if the data value is more than 3 standard deviations away from the average
    if (fabs(data - average) > 3 * standardDeviation) {
        return true;  // Data value is an outlier
    }

    return false;  // Data value is not an outlier
}