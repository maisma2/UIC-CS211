/*
 * TODO: Add file name, author, date, purpose
 */

#ifndef _SAMPLEGROUP_H
#define _SAMPLEGROUP_H

#include <cstdlib>
#include <iostream>
#include "sample.h"

using namespace std;  // Debatable.  Easier for now.

class SampleGroup {

    // Protected data memebers are accessible to descendants

protected:
    Sample ** samples; // Dynamic array of POINTERS TO Sample objects
    int nSamples;

    // Private data memebers - Descendants don't need access to these?

private:
    int nAllocated;
    double average;
    double xRange[ 2 ];
    double yRange[ 2 ];
    double dataRange[ 2 ];

    // Public methods

public:

    // Two constructors and one destructor
    SampleGroup( );
    SampleGroup( int initialCapacity );
    virtual ~SampleGroup( );

    int getNumberOfSamples( ) const;
    virtual bool addSample( const Sample & sample ); // Child can override this
    virtual bool addSample( Sample * samplePtr ); // Child can override this
    Sample * getSampleByID( int id ) const;
    bool isWithinBounds( const Sample & sample ) const;
    void printStats( ostream & out ) const;
    void printAll( ostream & out ) const;
    void calculateBounds();


    const double *getXRange() const;

    const double *getYRange() const;
};

#endif //_SAMPLEGROUP_H
