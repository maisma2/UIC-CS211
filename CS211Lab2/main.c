/* Lab2a.c

	Sample code for CS 211 Lab Exercise 2, Summer 2023
*/
/*
#include <stdlib.h>
#include <stdio.h>

int main( void ) {
	/*
	/* Question 1 and 2
	int var1[ 20 ];
	int *var2;
	
	printf( "Sizeof var1: %ld\n", sizeof ( var1 ) );
	printf( "Sizeof var2: %ld\n", sizeof ( var2 ) );
	
	/* Question 3
	printf( "Value of var1: %p\n", var1 );
	printf( "Address of var1: %p\n", &var1 );
	printf( "Address of var1[0]: %p\n", &var1[ 0 ] );
	var1[ 0 ] = 1;
	
	printf( "Value of var2: %p\n", var2 );
	printf( "Address of var2: %p\n", &var2 );
	printf( "Address of var2[0]: %p\n", &var2[ 0 ] );
	// var2[ 0 ] = 2;
	
	*/
	/* Questions 4 and 5
	int arr1[ 10 ];
	int arr2[ 10 ];
	int arr3[ 10 ];
	int i;
	
	for( i = 0; i < 10; i++ )	{
		arr1[ i ] = 100 + i;
		arr3[ i ] = 300 + i;
	}
	
	for( i = 0; i < 15; i++ )	{
		arr2[ i ] = 200 + i;
	}
	
	printf( "arr1: " );
	for( i = 0; i < 10; i++ )
		printf( "%d, ", arr1[ i ] );
	printf( "\n" );
	
	printf( "arr2: " );
	for( i = 0; i < 10; i++ )
		printf( "%d, ", arr2[ i ] );
	printf( "\n" );
	
	printf( "arr3: " );
	for( i = 0; i < 10; i++ )
		printf( "%d, ", arr3[ i ] );
	printf( "\n" );
	
	return 0;
}
*/
/* Lab2b.c

More sample code for CS 211 Lab Exercise 2, Summer 2023.
*/

/* Lab2b.c

	More sample code for CS 211 Lab Exercise 2, Summer 2023.
*/

#include <stdlib.h>
#include <stdio.h>

int main ( void ) {

    int * arr1;
    int size1 = 100;
    int arr2[ 100 ];

    /* QUESTION 6  and 7 */
    /* some information about the sizeof() function */
    printf( "Sizeof int:   %ld\n", sizeof( int ) );
    printf( "Sizeof size1: %ld\n", sizeof( size1 ) );
    printf( "Sizeof int*:  %ld\n", sizeof( int * ) );
    printf( "Sizeof arr1:  %ld\n", sizeof( arr1 ) );
    printf( "Sizeof arr2:  %ld\n", sizeof( arr2 ) );

    printf( "Initial address of arr1: %p\n", arr1 );

    /* allocate an array of "size1" values */
    arr1 = ( int * ) malloc( sizeof( int ) * size1 );

    printf( "New address of arr1: %p\n", arr1 );

    printf("----------------------------------------\n");

    /* QUESTION 8 */
    /* store values into the dynamically allocated array                     */
    /* - NOTE: we would normally just use the value in "size1" and not "max" */
    /*    "max" is used to correspond to Question 8 in the lab exercise      */
    int max = 200;
    int i;
    for( i = 0; i < max; i++ ) {
        arr1[ i ] = i;
    }

    /* print out the values just stored into the array */
    printf( "\nThe original values in the array:\n" );
    for( i = 0; i < max; i++ ) {
        printf( "%7d", arr1[ i ] );
        if( ( i + 1 ) % 10 == 0 )
            printf( "\n" );
    }
    printf( "\n" );

    int originalSize = size1;

    /* QUESTION 10 */
    /* code from Programming Project 1 description to "grow the array" */
    /* - modified so the variable names match the above code           */
    /* - this code will double the size of the current array           */

    /* set temp to refer to the location in memory of the larger array */
    int * temp;
    temp = arr1;         /* REAL LINE OF CODE FOR QUESTION 10 */

    /* allocate new space for the larger array */
    arr1 = ( int * ) malloc ( 2 * size1 * sizeof( int ) );

    /* copy the existing values from the original array to the larger array */
    for( i = 0; i < size1; i++ )
        arr1[ i ] = temp[ i ];

    /* return the allocated memory from the original array back to the OS */
    free( temp );
    temp = NULL;  /* For safety sake, to make sure we don't try to use it anymore. */

    /* update the size1 variable to properly reflect the current size of the array */
    size1 = size1 * 2;

    /* Now that the array has "grown" add some more values */
    /* add some new values into the array */
    for( i = originalSize; i < size1; i++ ) {
        arr1[ i ] = 1000 + i;
    }

    /* print out the values just stored into the array */
    printf( "\nThe current values in the array:\n" );
    for( i = 0; i < size1; i++ ) {
        printf( "%7d", arr1[ i ] );
        if( ( i + 1 ) % 10 == 0)
            printf( "\n" );
    }
    printf( "\n" );

    return 0;
}