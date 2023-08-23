/**
 *  TODO:  Add filename, author, date, purpose
 */


#ifndef _ANALYZEDSET_H
#define _ANALYZEDSET_H

#include "sampleGroup.h"


class AnalyzedSet : public SampleGroup {

private:
    // Private data
    double dDataDx, dDataDy;

    // Private methods
    void calculateSlopes( );
    bool isDuplicate( const Sample & sample ) const;
    Sample * findMaxX( ) const;
    Sample * findMinX( ) const;
    Sample * findMaxY( ) const;
    Sample * findMinY( ) const;

public:

    // Constructors and destructor
    AnalyzedSet( );
    AnalyzedSet( int initialCapacity );
    ~AnalyzedSet( );

    virtual bool addSample( const Sample & sample );
    virtual bool addSample(  Sample * samplePtr );
    double getDerivativeX( ) const;
    double getDerivativeY( ) const;
    bool isOutlier(const Sample& sample) const;
};

// TODO:  Add a means of printing AnalyzedSets, either as class methods or by operator <<

#endif // _ANALYZEDSET_H
