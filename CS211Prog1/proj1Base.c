/*  proj1Base.c

	Written [date] by [author] for CS 211, Summer 2023
	
	This program . . . 
	
	TODO:  Update this comment, including file name adjustment as needed
*/

#include <stdlib.h>
#include <stdio.h>

int main( void ) {

	int val;
	
	/* Create a dynamically allocated array of ints, with initial size 100 */
	
	/* Prompt the user for input */
	printf( "Enter in a list of numbers to be stored in a dynamic array.\n" );
	printf( "End the list with the terminal value of -999\n" );
	
	/* loop until the user enters -999 */
	scanf( "%d", &val );
	while( val != -999 ) {
		
		/* Store the value into an array, growing array if needed. */
		/* Double the array size whenever more space is needed. */
		
		/* get next value */
		scanf( "%d", &val );
	}
	
	/* Call function to make a copy of the array of values. */
	
	/* Call function to sort one of the arrays. */
	
	/* Call function to count matches, and report results. */
	
	/* Now check target numbers to see if they are in the list and where. */
	
	/* loop until the user enters -999 */
	printf( "Enter in a list of numbers to search for.  \n" );
	printf( "End the list with a terminal value of -999\n" );
	
	scanf( "%d", &val );	
	while( val != -999 ) {
		/* call function to perform target search operation */
		
		/* print out info about the target search results  */
		
		/* get next value */
		scanf( "%d", &val );
	}
	
	/* Final results could be printed here, such as the total # found, etc. */
	printf( "Good bye\n" );
	
	return 0;
} 
