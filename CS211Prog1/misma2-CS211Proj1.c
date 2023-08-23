/*  misma2-proj1Base.c
    Name: Abeer Ismail
    Date: 5/16/2023
    CS 211 Summer 2023
    IDE: Clion Windows 11
*/

#include <stdlib.h>
#include <stdio.h>

void copyArray(int fromArray[], int toArray[], int size){ //Copies one array to another to not lose the original data
    for (int i = 0; i < size; ++i) {
        toArray[i] = fromArray[i];
    }
}
void swap(int *a, int *b){ //Swaps two elements using pointers and dereferencing
    int temp = *a;
    *a = *b;
    *b = temp;
}
void myFavoriteSort(int array[], int size){ //Simple bubble sort, swap is done in previous function
    int i, j;
    for (i = 0; i < size-1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) //Comparison operator to see if the first element is greater than the second
                swap(&array[j], &array[j + 1]);
        }
    }
}
int countMatches(int arr[], int sorted[], int size){ //Goes through both arrays and counts the number of matches
    int counter = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] == sorted[i]){
            counter++;
        }
    }
    return counter;
}
int findInList(int arr[], int sorted[], int size, int target, int* nfound, int* index){ //This function traverses 1 by 1 the list and finds any matches and reports back the numbers
    *nfound = 0;
    *index = -1;
    int foundInPosition = 0;

    for (int i = 0; i < size; i++) { //Goes through one by one with comparisons
        if (sorted[i] == target) {
            (*nfound)++;
            if (arr[i] == target) {
                if (*index == -1) {
                    *index = i;
                }
                foundInPosition = 1;
            }

        }
        else if (sorted[i] > target){
            break;
        }
    }

    if (*nfound > 0) { //Returns if value was found as a bool
        if (foundInPosition) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return -1;
    }

}
int main( void ) {

    int val;
    int count = 0;

    /* Create a dynamically allocated array of ints, with initial size 100 */
    int size = 100;
    int* arr = (int*) malloc(size * sizeof(int));
    /* Prompt the user for input */
    printf( "Enter in a list of numbers to be stored in a dynamic array.\n" );
    printf( "End the list with the terminal value of -999\n" );

    /* loop until the user enters -999 */
    scanf( "%d", &val );
    while( val != -999 ) {
        /* Store the value into an array, growing array if needed. */
        /* Double the array size whenever more space is needed. */
        if (count == size){
            size *= 2;
            arr = (int*) realloc(arr, size * sizeof(int));
        }
        /* get next value */
        arr[count++] = val;
        scanf( "%d", &val );
    }

    /* Call function to make a copy of the array of values. */
    int* copy = (int*) malloc(count * sizeof(int));
    copyArray(arr, copy, count);
    /* Call function to sort one of the arrays. */
    myFavoriteSort(copy, count);
    /* Call function to count matches, and report results. */
    /* Now check target numbers to see if they are in the list and where. */
    int matches = countMatches(arr, copy, count);
    printf("There were %d matches.\n", matches);


    /* loop until the user enters -999 */
    printf( "Enter in a list of numbers to search for.  \n" );
    printf( "End the list with a terminal value of -999\n" );

    scanf( "%d", &val );
    while( val != -999 ) { //This loops runs through each number input and searches it, and then prints out the result
        /* call function to perform target search operation */
        int nfound, index;
        /* print out info about the target search results  */
        int result = findInList(arr, copy, count, val, &nfound, &index);
        if (result == -1){
            printf("Target: %d was not found.\n", val);
        }
        else {
            printf("Target: %d was found %d times.\n", val, nfound);
        }
        /* get next value */
        scanf( "%d", &val );
    }

    /* Final results could be printed here, such as the total # found, etc. */
    printf( "Good bye\n" );

    //Free the memory used by the arrays
    free(arr);
    free(copy);
    return 0;
}
