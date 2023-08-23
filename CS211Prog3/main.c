/* CS211 Summer 2023 Project 3
        Name: Abeer Ismail
    Date: 5/23/2023
    CS211 Summer 2023
    A Linked List Program and traversing the data
*/

#include <stdio.h>
#include <stdlib.h>

//Structs for creating the list and nodes
typedef struct sampleNode {
    int ID;
    struct sampleNode* next;
} SampleNode;

typedef struct {
    SampleNode* samples;
    int nSamples;
    int min, max;
} DataSet;

int addSampleToDataSet( DataSet * set, int sampleID );
SampleNode * findSampleInDataSet( DataSet set, int sampleID, int * location );
int size( DataSet set );
int isEmpty( DataSet set );
int remove1stSampleFromDataSet( DataSet * set );
int DebugMode = 0;

int main( int argc, char const *argv[ ] )
{
    //Checks for Debug
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-' && argv[i][1] == 'd') {
            DebugMode = 1;
            break;
        }
    }

    //Sets up the linked list to default values
    DataSet set;
    set.samples = NULL;
    set.nSamples = 0;

    // Set initial min and max to arbitrary lows and high these get replaced soon
    set.min = -100;
    set.max = 100;


    printf("Enter the sample IDs, negative ID to stop: \n");
    int sampleID;
    while(1) { //Keeps running forever until a negative sampleID
        scanf("%d", &sampleID);
        if(sampleID < 0)
            break;
        if(addSampleToDataSet(&set, sampleID) == -1) {
            printf("Failed to add sample %d\n", sampleID);
        }
    }

    printf("This data set has %d samples, with the lowest ID being %d and highest ID being %d.\n", size(set), set.min, set.max);

    printf("Enter the sample IDs to search in the dataset (negative to stop):\n");
    while(1) { //Same as earlier of running forever
        scanf("%d", &sampleID);
        if(sampleID < 0)
            break;
        int location;
        SampleNode* foundSample = findSampleInDataSet(set, sampleID, &location); //We run the function below
        if(foundSample != NULL) {
            printf("Sample %d was found at location %d, address %p\n", sampleID, location, foundSample);
        } else {
            printf("Sample %d was not found in the dataset.\n", sampleID);
        }
    }

    // Freeing all the memory individually.
    while(!isEmpty(set)) {
        remove1stSampleFromDataSet(&set);
    }


    return 0;

}

int addSampleToDataSet( DataSet * set, int sampleID ) {

    SampleNode *node = malloc(sizeof(SampleNode)); //Create dynamic linked list
    if (!node) {
        return -1;
    }

    //Set values for each node, and list
    node->ID = sampleID;
    node->next = set->samples;
    set->samples = node;
    set->nSamples++;

    //Setting the range to traverses the IDs
    if(set->nSamples == 1 || sampleID < set->min)
        set->min = sampleID;

    if(set->nSamples == 1 || sampleID > set->max)
        set->max = sampleID;

    return 0;
}


SampleNode* findSampleInDataSet( DataSet set, int sampleID, int * location ){
    *location = 0; //sets the starter point
    SampleNode *curr = set.samples;

    while(curr != NULL){ //As we go through the list until we hit NULL and stop when we hit the correct ID
        if(curr->ID == sampleID)
            return curr;
        curr = curr->next;
        (*location)++;
    }

    *location = -1;
    return NULL;
}


int size( DataSet set ){
    return set.nSamples; //We set size when putting in each Sample, we could also use a simple traversing method and counter as well
}


int isEmpty( DataSet set ){
    return set.samples == NULL; //Checks if the first value (since we set it NULL at start) if it's NULL still then its empty, but also traverse and count works
}


int remove1stSampleFromDataSet( DataSet * set ){
    if(isEmpty(*set)) return -1; //Check if its empty first

    SampleNode *firstSampleNode = set->samples; //To make sure we don't mess up original list
    int sampleID = firstSampleNode->ID;
    set->samples = firstSampleNode->next;

    free(firstSampleNode);
    firstSampleNode = NULL; //Safety case to set pointer to NULL

    set->nSamples--;

    return sampleID;
}