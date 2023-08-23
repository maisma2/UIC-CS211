/*  CS211 Summer 2023 Project 2
    Name: Abeer Ismail
    5/20/2023
    Reading data files and storing them in a data structure
*/

#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 100 // Initial size of the array of samples, looking at the data points this allocates more than necessary space
#define X 0 // X is 0 and Y is 1 so these two do not access the same parts of the array
#define Y 1

int DebugMode = 0; // Global variable DebugMode, checks for -d arg when running by default it's off

//Structs used for each coord point
typedef struct Sample { //Takes an ID, coord point, and data value
    int ID;
    double coordinates[2];
    double data;
} Sample;

typedef struct SampleGroup { //Takes a sample struct, and the number of samples, and the average data value, and the range of the data values
    Sample *samples;
    int nAllocated;
    int nSamples;
    double average;
    double xRange[2], yRange[2], dataRange[2];
} SampleGroup;


// Add methods to set points
int addSampleToGroup( SampleGroup * groupPtr, Sample sample );
int withinBounds( SampleGroup group, Sample sample );
// Print method(s)
void printSampleGroup(SampleGroup group);
void printSample(Sample sample);


int main( int argc, char const *argv[ ] ) {

    //First we check for debug mode if it's on or off, this implementation goes through every command line argument and checks for "-d" rather than it being the first argument
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-' && argv[i][1] == 'd') {
            DebugMode = 1;
            break;
        }
    }

    //Struct setup
    SampleGroup group; //Where all the samples are placed into
    group.samples = malloc(INIT_SIZE * sizeof(Sample)); //Allocates memory for the samples, while using the sample struct as the memory type
    group.nAllocated = INIT_SIZE; //Sets the number of allocated samples to the initial size
    group.nSamples = 0; //Sets the number of samples to 0
    group.average = 0; //Sets the average to 0
    group.xRange[0] = group.yRange[0] = group.dataRange[0] = 0; //Sets the lower bounds of the ranges to 0, this can be done in 3 lines rather than 1
    group.xRange[1] = group.yRange[1] = group.dataRange[1] = 0; //Sets the upper bounds of the ranges to 0, this can be done in 3 lines rather than 1

    Sample temp; //Temporary holder to place into SampleGroup
    double totalData = 0.0; //Set to 0 to add the values later
    int id = 0; //ID counter


    while (scanf("%lf %lf %lf", &temp.coordinates[X], &temp.coordinates[Y], &temp.data) == 3) { //Takes 3 float values, places them into the temp struct. Has to be 3 values
        if (temp.data < -1000.0) break; //This is the break case
        temp.ID = id++;
        addSampleToGroup(&group, temp); //Adds the temp struct to the group

        if (group.nSamples == 1) { //If there is only 1 sample, set the ranges to the first sample
            group.xRange[0] = group.xRange[1] = temp.coordinates[X];
            group.yRange[0] = group.yRange[1] = temp.coordinates[Y];
            group.dataRange[0] = group.dataRange[1] = temp.data;
        }
        else { //If there is more than 1 sample, check if the ranges need to be updated
            if (temp.coordinates[X] < group.xRange[0]) group.xRange[0] = temp.coordinates[X];
            if (temp.coordinates[X] > group.xRange[1]) group.xRange[1] = temp.coordinates[X];
            if (temp.coordinates[Y] < group.yRange[0]) group.yRange[0] = temp.coordinates[Y];
            if (temp.coordinates[Y] > group.yRange[1]) group.yRange[1] = temp.coordinates[Y];
            if (temp.data < group.dataRange[0]) group.dataRange[0] = temp.data;
            if (temp.data > group.dataRange[1]) group.dataRange[1] = temp.data;
        }

        totalData += temp.data;
        group.average = totalData / group.nSamples; //Sets the average to the total data divided by the number of samples
    }

    printSampleGroup(group);

    //Printing the samples
    while (scanf("%lf %lf", &temp.coordinates[X], &temp.coordinates[Y]), &temp.data == 3) {
        if (temp.data < -1000.0) break;

        printf("Sample (%.2lf, %.2lf, %.2lf) is %s\n", temp.coordinates[X], temp.coordinates[Y], temp.data,
               withinBounds(group, temp) ? "within bounds" : "out of bounds"); //Prints 3 floating points, and then a ternary condition to see if it's within bounds or not
    }

    free(group.samples); //Frees the memory allocated, the rest are put on stack and don't need to be cleared
    return 0;

}

/* TODO: function definitions */

int addSampleToGroup( SampleGroup *groupPtr, Sample sample ){
    //Checks to resizing the array (this shouldn't be needed, for the sample sets)
    if (groupPtr->nSamples == groupPtr->nAllocated) { //If the number of samples is equal to the number of allocated samples, then we need to allocate more memory
        groupPtr->nAllocated *= 2; //Double the number of allocated samples
        Sample *temp = realloc(groupPtr->samples, groupPtr->nAllocated * sizeof(Sample)); //Reallocates memory for the samples, while using the sample struct as the memory type
        if (temp == NULL) {
            return -1;
        }
        groupPtr->samples = temp;
    }

    //Add the sample in
    groupPtr->samples[groupPtr->nSamples++] = sample; //Adds the sample into the array, and then increments the number of samples

    //Updating the bounds
    if(groupPtr->nSamples == 1){ //First sample to fix the bounds
        groupPtr->xRange[0] = groupPtr->xRange[1] = sample.coordinates[X];
        groupPtr->yRange[0] = groupPtr->yRange[1] = sample.coordinates[Y];
        groupPtr->dataRange[0] = groupPtr->dataRange[1] = sample.data;
    } else { //Checks to see if we need to fix the other bounds
        if(sample.coordinates[X] < groupPtr->xRange[0]) groupPtr->xRange[0] = sample.coordinates[X];
        if(sample.coordinates[X] > groupPtr->xRange[1]) groupPtr->xRange[1] = sample.coordinates[X];
        if(sample.coordinates[Y] < groupPtr->yRange[0]) groupPtr->yRange[0] = sample.coordinates[Y];
        if(sample.coordinates[Y] > groupPtr->yRange[1]) groupPtr->yRange[1] = sample.coordinates[Y];
        if(sample.data < groupPtr->dataRange[0]) groupPtr->dataRange[0] = sample.data;
        if(sample.data > groupPtr->dataRange[1]) groupPtr->dataRange[1] = sample.data;
    }
    return 0;

}

int withinBounds( SampleGroup group, Sample sample ) {
    if (group.nSamples == 0){ //Nothing in samples nothing to check
        return 0;
    }
    if (sample.coordinates[X] >= group.xRange[0] && sample.coordinates[X] <= group.xRange[1] &&  //First line is X coords, Then Y coords, then Data coords to check bounds
        sample.coordinates[Y] >= group.yRange[0] && sample.coordinates[Y] <= group.yRange[1] &&
        sample.data >= group.dataRange[0] && sample.data <= group.dataRange[1]){
        return 1;
    }
    return 0; //Debug reasons
}

void printSample(Sample sample) { //Prints individual samples
    printf("Sample (%.2lf, %.2lf, %.2lf)\n", sample.coordinates[X], sample.coordinates[Y], sample.data);
}

void printSampleGroup(SampleGroup group){ //First part is data stats, second part loops through
    printf("Sample Group - X Range: [%.2f, %.2f], Y Range: [%.2f, %.2f], Data Range: [%.2f, %.2f], Number of Samples: %d\n",
           group.xRange[0], group.xRange[1],
           group.yRange[0], group.yRange[1],
           group.dataRange[0], group.dataRange[1],
           group.nSamples);

    // Print all samples in the group
    for(int i = 0; i < group.nSamples; i++) {
        printf("Sample %d:\n", i);
        printSample(group.samples[i]);
    }
}

