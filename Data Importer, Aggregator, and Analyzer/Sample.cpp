/*
 * TODO: Add file name, author, date, purpose
 */

#include "sample.h"

using namespace std; // Debatable, but easier for now.

int Sample::nextID = 1;

Sample::Sample(double X, double Y, double data) {
    ID = nextID++;
    coordinates[0] = X;
    coordinates[1] = Y;
    this->data = data;
}

Sample::Sample(const Sample& sample) {
    ID = nextID++;
    coordinates[0] = sample.coordinates[0];
    coordinates[1] = sample.coordinates[1];
    data = sample.data;
}

Sample::~Sample() {
}

int Sample::getID() const {
    return ID;
}

double Sample::getX() const {
    return coordinates[0];
}

double Sample::getY() const {
    return coordinates[1];
}

double Sample::getData() const {
    return data;
}

ostream& operator<<(ostream& out, const Sample& sample) {
    out << "Sample ID: " << sample.getID() << ", X: " << sample.getX()
        << ", Y: " << sample.getY() << ", Data: " << sample.getData();
    return out;
}