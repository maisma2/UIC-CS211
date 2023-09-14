/*
 * Name: Abeer Ismail
 * 5/29/2023
 * CS211 Summer 2023
 * This Project is a shared list of subsets of data collected for a science experiment. This uses dyanmic arrays and linked lists.
 */

#include <stdio.h>
#include <stdlib.h>

//Same values are previous project, X is 0 and Y is 1 to not overlap during data access in Array
#define INIT_SIZE 100 //initial size of the array
#define X 0
#define Y 1

//Same structs as Program 2 as well for Samples and Struct Groups, temp Samples gets inserted into SampleGroups, SampleNode is a linked list, Subset is a group of samples
typedef struct Sample {
    int ID;
    double coordinates[2];
    double data;
} Sample;

typedef struct SampleGroup {
    Sample *samples;
    int nAllocated;
    int nSamples;
    double average;
    double xRange[2], yRange[2], dataRange[2];
} SampleGroup;

typedef struct SampleNode {
    Sample *sample;
    struct SampleNode *next;
} SampleNode;

typedef struct Subset {
    int ID;
    SampleNode *samples;
    int nSamples;
    double average;
    double xRange[2], yRange[2], dataRange[2];
} Subset;

//Functions will be finished lower in the code
int addSampleToGroup(SampleGroup *groupPtr, Sample sample);
int withinBounds(SampleGroup group, Sample sample);
void printSampleGroup(SampleGroup group);

int DebugMode = 0;
int main(int argc, char const *argv[ ]) {

    for (int i = 1; i < argc; ++i) {//Runs through the entire argument section and finds -d to turn on DebugMode
        if (argv[i][0] == '-' && argv[i][1] == 'd') {
            DebugMode = 1;
            break;
        }
    }

    SampleGroup allSamples;
    Sample temp;

    //Setting up default values for both objects, allSamples and temp.
    allSamples.samples = malloc(INIT_SIZE * sizeof(Sample)); //Allocates memory for the array of samples
    allSamples.nAllocated = INIT_SIZE;
    allSamples.nSamples = 0;
    allSamples.average = 0;
    allSamples.xRange[0] = allSamples.yRange[0] = allSamples.dataRange[0] = 0;
    allSamples.xRange[1] = allSamples.yRange[1] = allSamples.dataRange[1] = 0;

    double totalData = 0.0;
    int id = 0;

    //Scanning through each line of the input to add into the coords and data fields of temp Sample
    while(scanf("%lf %lf %lf", &temp.coordinates[X], &temp.coordinates[Y], &temp.data) == 3) {
        if (temp.data < -1000.0) break; //Break case when data field is lower than -1000.
        temp.ID = id++;
        addSampleToGroup(&allSamples, temp);

        if (allSamples.nSamples == 1) { //First sample sets the range
            allSamples.xRange[0] = allSamples.xRange[1] = temp.coordinates[X];
            allSamples.yRange[0] = allSamples.yRange[1] = temp.coordinates[Y];
            allSamples.dataRange[0] = allSamples.dataRange[1] = temp.data;
        } else { //Other samples get tested here, if they are lower or higher than the current range, they get set as the new range
            if (temp.coordinates[X] < allSamples.xRange[0])
                allSamples.xRange[0] = temp.coordinates[X];
            if (temp.coordinates[X] > allSamples.xRange[1])
                allSamples.xRange[1] = temp.coordinates[X];
            if (temp.coordinates[Y] < allSamples.yRange[0])
                allSamples.yRange[0] = temp.coordinates[Y];
            if (temp.coordinates[Y] > allSamples.yRange[1])
                allSamples.yRange[1] = temp.coordinates[Y];
            if (temp.data < allSamples.dataRange[0])
                allSamples.dataRange[0] = temp.data;
            if (temp.data > allSamples.dataRange[1])
                allSamples.dataRange[1] = temp.data;
        }
        totalData += temp.data; //Adding the data together to find the sum
        allSamples.average = totalData / allSamples.nSamples; //Finding the average of all samples thus far
    }

    printSampleGroup(allSamples);

    //Now creating subset groups for samples
    Subset *sets = NULL;
    int numSets = 0;

    int subsetID;
    while (scanf("%d", &subsetID) == 1){
        if (subsetID < 0) {
            if (sets != NULL && sets[numSets - 1].nSamples == 0) break; //Break case if sets aren't at default values

            //Default values for the subsets since we already checked the sets are empty
            sets = realloc(sets, (numSets + 1) * sizeof(Subset));
            sets[numSets].ID = numSets;
            sets[numSets].samples = NULL;
            sets[numSets].nSamples = 0;
            sets[numSets].average = 0;
            sets[numSets].xRange[0] = sets[numSets].yRange[0] = sets[numSets].dataRange[0] = 0;
            sets[numSets].xRange[1] = sets[numSets].yRange[1] = sets[numSets].dataRange[1] = 0;
            numSets++;

        }
        else{
            if (subsetID >= 0 && subsetID < allSamples.nSamples){
                SampleNode *node = malloc(sizeof(SampleNode)); //Allocating memory for the node
                //Creating the links for the subsets
                node->sample = &allSamples.samples[subsetID];
                node->next = NULL;

                if (sets != NULL){ //If sets aren't at default values, we can add the sample to the subset
                    if (sets[numSets - 1].samples == NULL){
                        sets[numSets - 1].samples = node;
                    }
                    else {
                        SampleNode *current = sets[numSets - 1].samples;
                        while (current->next != NULL)
                            current = current->next;
                        current->next = node;
                    }
                    sets[numSets - 1].nSamples++;
                }
                // Freeing the node memory for *node
                if (sets == NULL || sets[numSets - 1].samples == NULL) {
                    free(node);
                }
            }
        }
    }

    //This is finding the average and range(s) for each subset, it first checks we need to find an average by looking for NULL, then it traverses and finds the limits and adds to a sum and counter.
    for (int i = 0; i < numSets; i++) {
        SampleNode *current = sets[i].samples;
        double totalData = 0.0;
        int count = 0;

        // Default values for the subsets since we already checked the sets are empty
        sets[i].xRange[0] = sets[i].xRange[1] = 0.0;
        sets[i].yRange[0] = sets[i].yRange[1] = 0.0;
        sets[i].dataRange[0] = sets[i].dataRange[1] = 0.0;

        while (current != NULL) { //setting values for the subsets
            totalData += current->sample->data;

            if (current->sample->coordinates[X] < sets[i].xRange[0])
                sets[i].xRange[0] = current->sample->coordinates[X];
            if (current->sample->coordinates[X] > sets[i].xRange[1])
                sets[i].xRange[1] = current->sample->coordinates[X];
            if (current->sample->coordinates[Y] < sets[i].yRange[0])
                sets[i].yRange[0] = current->sample->coordinates[Y];
            if (current->sample->coordinates[Y] > sets[i].yRange[1])
                sets[i].yRange[1] = current->sample->coordinates[Y];
            if (current->sample->data < sets[i].dataRange[0])
                sets[i].dataRange[0] = current->sample->data;
            if (current->sample->data > sets[i].dataRange[1])
                sets[i].dataRange[1] = current->sample->data;

            count++;
            current = current->next;
        }

        if (count > 0) { //safety case for sample checking otherwise the output is nan for sample data provided.
            sets[i].average = totalData / count;
        } else {
            sets[i].average = 0.0;
        }
    }

    //Printing out Subset data and the overall statistics by looking at sets object. Rather than one line for readability it's printed on multiple.
    printf("Subset Data:\n");
    for (int i = 0; i < numSets; i++) {
        printf("Subset %d:\n", sets[i].ID);
        printf("  Average=%.2lf\n", sets[i].average);
        printf("  X Range=[%.2lf, %.2lf]\n", sets[i].xRange[0], sets[i].xRange[1]);
        printf("  Y Range=[%.2lf, %.2lf]\n", sets[i].yRange[0], sets[i].yRange[1]);
        printf("  Data Range=[%.2lf, %.2lf]\n", sets[i].dataRange[0], sets[i].dataRange[1]);
    }

    //Now we check the second set and finding subsets
    Sample secondSample;
    while (scanf("%lf %lf %lf", &secondSample.coordinates[X], &secondSample.coordinates[Y], &secondSample.data) == 3) { //Scans each line for 3 values and inputs them
        if (secondSample.data < -1000.0) break; //Break case for data values lower than -1000

        int belongsToSubset = -1;
        for (int i = 0; i < numSets; i++) {
            if (withinBounds(allSamples, secondSample)) { //If it's within the bounds of the sample group, we can check if it's within the subset
                belongsToSubset = sets[i].ID;
                break;
            }
        }

        //Printing the data out
        if (belongsToSubset != -1) {
            printf("Sample (%.2lf, %.2lf, %.2lf) belongs to Subset %d", secondSample.coordinates[X], secondSample.coordinates[Y], secondSample.data, belongsToSubset);
            if (secondSample.data < sets[belongsToSubset].dataRange[0] ||
                secondSample.data > sets[belongsToSubset].dataRange[1]) {
                printf(" (outlier)");
            }
            printf("\n");
        }
    }
    //Memory freeing by nulling the linked List and freeing the sets
    for (int i = 0; i < numSets; i++) {
        SampleNode *current = sets[i].samples;
        while (current != NULL) {
            SampleNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(sets);
    free(allSamples.samples);

    return 0;

}

int addSampleToGroup(SampleGroup *groupPtr, Sample sample){

    if (groupPtr->nSamples == groupPtr->nAllocated) { //Checks of samples are the same as allocated space, if so we double the size
        groupPtr->nAllocated *= 2;
        Sample *temp = realloc(groupPtr->samples, groupPtr->nAllocated * sizeof(Sample));
        if (temp == NULL) {
            return -1;
        }
        groupPtr->samples = temp;
    }
    groupPtr->samples[groupPtr->nSamples++] = sample;

    if (groupPtr->nSamples == 1) { //Sets the range of the group to the first sample
        groupPtr->xRange[0] = groupPtr->xRange[1] = sample.coordinates[X];
        groupPtr->yRange[0] = groupPtr->yRange[1] = sample.coordinates[Y];
        groupPtr->dataRange[0] = groupPtr->dataRange[1] = sample.data;
    } else { //If not the first sample, we set the ranges accordingly
        if (sample.coordinates[X] < groupPtr->xRange[0])
            groupPtr->xRange[0] = sample.coordinates[X];
        if (sample.coordinates[X] > groupPtr->xRange[1])
            groupPtr->xRange[1] = sample.coordinates[X];
        if (sample.coordinates[Y] < groupPtr->yRange[0])
            groupPtr->yRange[0] = sample.coordinates[Y];
        if (sample.coordinates[Y] > groupPtr->yRange[1])
            groupPtr->yRange[1] = sample.coordinates[Y];
        if (sample.data < groupPtr->dataRange[0])
            groupPtr->dataRange[0] = sample.data;
        if (sample.data > groupPtr->dataRange[1])
            groupPtr->dataRange[1] = sample.data;
    }

    return 0;
}

int withinBounds(SampleGroup group, Sample sample) { //Checks if the sample is within the bounds of the group using simple comparison operators
    if (group.nSamples == 0) {
        return 0;
    }

    if (sample.coordinates[X] >= group.xRange[0] && sample.coordinates[X] <= group.xRange[1] &&
        sample.coordinates[Y] >= group.yRange[0] && sample.coordinates[Y] <= group.yRange[1] &&
        sample.data >= group.dataRange[0] && sample.data <= group.dataRange[1]) {
        return 1;
    }

    return 0;
}

void printSampleGroup(SampleGroup group) { //Printing the entire sample group, each line represents a value for readability
    printf("Sample Group:\n");
    printf("  X Range=[%.2lf, %.2lf]\n", group.xRange[0], group.xRange[1]);
    printf("  Y Range=[%.2lf, %.2lf]\n", group.yRange[0], group.yRange[1]);
    printf("  Data Range=[%.2lf, %.2lf]\n", group.dataRange[0], group.dataRange[1]);
    printf("  Number of Samples: %d\n", group.nSamples);

    for (int i = 0; i < group.nSamples; i++) {
        printf("Sample %d:\n", i);
        printf("  ID: %d\n", group.samples[i].ID);
        printf("  X: %.2lf\n", group.samples[i].coordinates[X]);
        printf("  Y: %.2lf\n", group.samples[i].coordinates[Y]);
        printf("  Data: %.2lf\n", group.samples[i].data);
    }
}

