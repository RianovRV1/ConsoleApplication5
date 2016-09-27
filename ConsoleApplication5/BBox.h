//////////////////////////////////////////////////////////////////////////////
//
//  --- BBox.h ---
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __BBOX_H__
#define __BBOX_H__

#include <iostream>
#include "Angel.h"

//----------------------------------------------------------------------------
//
//  --- BBox ---
//
/// \class BBox
/// \brief A class for storing a three-dimensional bounding box

struct BBox {

    typedef Angel::vec3  vec3;

    vec3 ll;  ///< lower-left corner of the bounding box
    vec3 ur;  ///< upper-right corner of the bouding box

    BBox() : ll(), ur() {}
    BBox( const vec3& ll, const vec3& ur ) : ll(ll), ur(ur) {}

    /// Merge two bounding boxes
    BBox merge( const BBox& bb ) const 
        { return BBox( Angel::min(ll, bb.ll), Angel::max(ur, bb.ur) ); }
    
    /// Return the center of the bounding box
    vec3 center() const 
        { return 0.5*(ur + ll); }

    /// Return the distance between opposite corners of the bounding box
    float diameter() const 
        { return length(ur - ll); }

    /// ostream insertion operator;
    friend std::ostream& operator << ( std::ostream& os, const BBox& b )
        { return os << b.ll << " -> " << b.ur; }
};

#endif // __BBOX_H__
