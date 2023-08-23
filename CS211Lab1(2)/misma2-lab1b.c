/*
 * Name: Abeer Ismail
 * Date: 5/15/2023
 * IDE: CLion, Windows 11
 * Class: CS 211 Summer 2023
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