/*
 * TODO: Add file name, author, date, purpose
 */


#ifndef _SAMPLE_H
#define _SAMPLE_H

#include <cstdlib>
#include <iostream>

using namespace std; // Debatable, but easier for now.

class Sample {

    /* Private data members */

private:
    int ID;
    static int nextID;
    double coordinates[ 2 ];
    double data;

    /* Public methods */

public:

    // Two constructors and one destructor
    Sample( double X, double Y, double data );
    Sample( const Sample & sample ); // Copy constructor
    ~Sample( );

    // Getters
    int getID( ) const;
    double getX( ) const;
    double getY( ) const;
    double getData( ) const;

};


// Function prototype.  The following is not a class method
ostream & operator << ( ostream & out, const Sample & sample );


#endif //_SAMPLE_H
