/*  Lab1a.c
    Last modified by John Bell for CS 211 Summer 2023
    This program illustrates * and & with ints and pointers
    Name: Abeer Ismail
    IDE: CLion
    Date: 5/15/2021
*/
// TODO:  Add more comments
/*
#include <stdlib.h>
#include <stdio.h>

void addFive ( int p1, int *p2 );

int main( void ) {

    int x = 7;
    int y;
    int *p = NULL;

    printf( "\nHello World\n" );
    printf( "Print line 0: x = %d\n", x );

    p = &x;
    y = *p;
    *p = x+y ;

    printf( "\nPrint line 1: x = %d\n", x );
    printf( "Print line 2: &x = %p\n", &x );

    printf( "\nPrint line 3: y = %d\n", y );
    printf( "Print line 4: &y = %p\n", &y );

    printf( "\nPrint line 5: p = %p\n", p );
    printf( "Print line 6: &p = %p\n", &p );
    printf( "Print line 7: *p = %d\n", *p );

    // printf ("Print line 8: %d\n", *x);

    int a = 2;
    int b = 4;

    printf( "\nBefore calling addFive( a, &b ):\n" );
    printf( "\tPrint line 11: For variable a: value: %d, address:  %p\n", a, &a );
    printf( "\tPrint line 12: For variable b: value: %d, address:  %p\n", b, &b );

    addFive ( a, &b );

    printf( "\nAfter calling addFive( a, &b ):\n" );
    printf("\tPrint line 13: For variable a: value: %d, address:  %p\n", a, &a );
    printf("\tPrint line 14: For variable b: value: %d, address:  %p\n", b, &b );
    printf( "\n" );
    return 0;
}


void addFive ( int p1, int *p2 ) {

    printf( "\nEntering addFive( int p1, int *p2 )\n" );
    printf( "\n\tPrint line 101: p1 = %d\n", p1 );
    printf( "\tPrint line 102: *p2 = %d\n", *p2 );

    printf( "\n\tPrint line 103: &p1 = %p\n", &p1 );
    printf( "\tPrint line 104: p2 = %p\n", p2 );
    printf( "\tPrint line 105: &p2 = %p\n", &p2 );

    p1 = p1 + 5;
    *p2 = *p2 + 5;

    printf( "\nExiting addFive( int p1, int *p2 )\n" );
    printf( "\n\tPrint line 106: p1 = %d\n", p1 );
    printf( "\tPrint line 107: *p2 = %d\n", *p2 );

    printf( "\n\tPrint line 108: &p1 = %p\n", &p1 );
    printf( "\tPrint line 109: p2 = %p\n", p2 );
    printf( "\tPrint line 110: &p2 = %p\n", &p2 );

    return;
}

*/

/*  Lab1b.c

    Last modified by        on       for CS 211
*/

#include <stdlib.h>
#include <stdio.h>

int main ( void ) {

    int val;
    double average;
    int count = 0; //To find averages
    int total = 0; //To find total sum for average


    /* prompt the user for input */
    printf( "Enter in a list of numbers followed by the terminal value of -999\n" );

    /* loop until the user enters -999 */
    scanf( "%d", &val );
    while( val != -999 ) {
        // Do something here with val.
        count++; //Adds a new value to average calc
        total += val; //Adds to the sum of all values

        // Then read in another one at the end of the loop.
        scanf( "%d", &val );
    }

    /* calculate the average of the values read in */
    if (count != 0) { //Safety case for division by 0
        average = (double) total / count; //we first cast as a double to avoid integer division, divided by total amount of numbers entered
    } else {
        average = 0;    //Safety case for if 0 numbers were entered
    }
    /* display the results */
    /* use the following printf statements to display the results */
    /* remove the comments */

    printf( "For the list of %d numbers with a total of %d,\n", count, total );
    printf( " the average is: %15.5f\n", average );

    return 0;
}