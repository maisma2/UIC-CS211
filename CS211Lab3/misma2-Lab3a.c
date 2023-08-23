/* Lab3.c
    Name: Abeer Ismail
    Date: 5/17/2023
    CS 211 Summer 2023
    IDE: Clion Windows 11

	This program uses structs, arrays, and pointers to store and
	process data samples, as might be collected by a drone or
	lunar rover.  Each data sample consists of a unique serial number,
	the ( x, y ) coordinates where the sample was collected,
	and a data value for the measured sample.  ( In practice the
	data could be pollution level, radiation, temperature,
	salinity, or any other sort of scientific measurements. )
*/

#include <stdio.h>
#include <stdlib.h>

/*CS 211 - Lab 3
  Please complete the tasks listed below. */


#define SIZE 10


/* Task 1 -- use typedef to create a type "Sample" */

typedef struct SAMPLE {
  int ID;				// Unique serial number for each Sample.
  double x, y;			// Location where sample was collected.
  double data;			// Data value at the sample point.
} Sample;

/* Function Prototypes, in order of appearance after main( ).
   Task 2 requires editing the two print functions to make them work. */

void printSampleByValue( Sample s );

void printSampleByAddress ( Sample * sPtr );

void initSample( Sample * sPtr );

Sample averageSamples( Sample s1, Sample s2 );


int main( void )  { // <------------------------------------------ Main

  int i;
  Sample s1;
  /* Task 3 -- Pass s1 to initSample, and then print it using
	printSampleByValue */
  initSample(&s1);
  printf( "Printing Sample s1 by Value:\n" );
    printSampleByValue(s1);

  /* Task 4 -- Declare a pointer of type Sample * named ptr1 */

  Sample* ptr1;

  /* Task 5 -- Dynamically allocate memory for the Sample pointed
     to by ptr1, and initialize it by calling initSample( ).
	 Then print it using printSampleByAddress */

   ptr1 = (Sample*) malloc(sizeof(Sample));
   initSample(ptr1);
   printf( "Printing Sample * ptr1 by Address:\n" );
   printSampleByAddress(ptr1);

  //Declaring two more samples s2 and s3
  Sample s2, s3;

  /* Task 6 requires editing averageSamples( ) - See below. */
    initSample(&s2);
    s3 = averageSamples(s1, s2);

  /* Task 7 -- Initialize s2 with initSample(), and then
     use averageSamples( ) to make s3 the average of s1 and s2.
     Print all three samples */
    printf( "s3 = average( s1, s2 ) ?:\n" );
    printSampleByValue(s1);
    printSampleByValue(s2);
    printSampleByValue(s3);


/************************************************/
/*************** Part 2 *************************/
/************************************************/
/* All three variables sArr, sPtr1, and sPtr2 are to be used to
   create arrays of 10 Samples each. */

  Sample    sArr[ SIZE ]; // Array of Samples on the stack.
  Sample * sPtr1[ SIZE ]; // Array of pointers on stack to Samples in the heap.
  Sample * sPtr2;         // Array of Samples on the heap


  /* Task 8 - Uncomment and complete the print in the loop: */

  printf( "Array of Samples sArr:\n" );
  for( i = 0; i < SIZE; ++i ) {
	     printf( "For position %d:  ", i );
	     initSample( &sArr[i] );
	     printSampleByValue(sArr[i]);
  }

/*Task 9 -- For array sPtr1 you must dynamically allocate space
  for each Sample, and then initialize and print each one. */

/***********************************/
/* sPtr1 : Declare, Initialize, Print */
/***********************************/
  for (int i = 0; i < SIZE; ++i){
        sPtr1[i] = (Sample*) malloc(sizeof(Sample));
        initSample(sPtr1[i]);
        printSampleByAddress(sPtr1[i]);
    }

/* Task 10 -- sPtr2 is a single pointer that must refer to an array of 10 instances
   allocated on the heap. Repeat the previous steps for sPtr2 by initializing and
   printing using proper functions*/

/***********************************/
/* sPtr2 : Declare, Initialize, Print */
/***********************************/

    sPtr2 = (Sample*) malloc(sizeof(Sample) * SIZE);
    for (int i = 0; i < SIZE; ++i){
        initSample(&sPtr2[i]);
        printSampleByAddress(&sPtr2[i]);
    }

  return 0;
}


/************************/
/* function definitions */
/************************/

/* Task 2 - Replace the numbers in the following two functions
   with fields from the Sample passed in as an argument.
   The int is the ID, and the 3 doubles are x, y, and data.
*/

void printSampleByValue( Sample s ) { // <------ Print by Value

  printf( "\tSample %d = ( %.2f, %.2f, %.2f ) \n", s.ID,s.x, s.y, s.data); //Regular print statement

}

void printSampleByAddress( Sample * s ) { // <--- Print by Address

  printf( "\tSample %d = ( %.2f, %.2f, %.2f ) \n", s->ID, s->x, s->y, s->data); //For pointers we use -> instead of .

}

/* In practice data samples would be collected by drone, robot,
   or maybe a scientist or intern.  We will simulate that data
   collection here with a random number generator. */

void initSample( Sample * s ) {// <------------------ initSample

  static int nextID = 0;
  s->ID = nextID++;
  s->x = ( rand( ) % 10000 ) / 100.0;
  s->y = ( rand( ) % 10000 ) / 100.0;
  s->data = ( rand( ) % 10000 ) / 100.0;

}

/* Task 6 - write the averageSamples() function definition.
   Output sample values should be the average of the input values,
   except the result gets a new unique ID through a call to initSample. */

Sample averageSamples( Sample s1, Sample s2 ) {

	/* Create a new Sample and initialize it with initSample( ). */
    Sample s4;
    initSample(&s4);

	/* Then calculate the average values for x, y, and data. */
    s4.x = (s1.x+s2.x)/2.0;
    s4.y = (s1.y+s2.y)/2.0;
    s4.data = (s1.data+s2.data)/2.0;
	/* Then return the result. */
    return s4;

}
