//////////////////////////////////////////////////////////////////////////////
//
//  --- vec.h ---
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ANGEL_VEC_H__
#define __ANGEL_VEC_H__

#include <cmath>
#include "Angel.h"

using namespace std;

namespace Angel {

//////////////////////////////////////////////////////////////////////////////
//
//  vec2 - 2D vector
//
//////////////////////////////////////////////////////////////////////////////

struct vec2 {

    GLfloat  x;
    GLfloat  y;

    //
    //  --- Constructors and Destructors ---
    //

    vec2( const GLfloat s = 0.0f ) :
        x(s), y(s) {}

    vec2( const GLfloat x, const GLfloat y ): 
        x(x), y(y) {}

    //
    //  --- Indexing Operator ---
    //

    GLfloat& operator [] ( int i ) { return *(&x + i); }
    GLfloat operator [] ( int i ) const { return *(&x + i); }

    //
    //  --- Equality Operators ---
    //

    bool operator == ( const vec2& v )
        { return x == v.x && y == v.y; }

    bool operator != ( const vec2& v )
        { return x != v.x || y != v.y; }

    //
    //  --- (non-modifying) Arithematic Operators ---
    //

    vec2 operator - () const // unary minus operator
        { return vec2( -x, -y ); }

    vec2 operator + ( const vec2& v ) const
        { return vec2( x + v.x, y + v.y ); }

    vec2 operator - ( const vec2& v ) const
        { return vec2( x - v.x, y - v.y ); }

    vec2 operator * ( const GLfloat s ) const
        { return vec2( s*x, s*y ); }

    vec2 operator * ( const vec2& v ) const
        { return vec2( x*v.x, y*v.y ); }

    friend vec2 operator * ( const GLfloat s, const vec2& v )
        { return v * s; }

    vec2 operator / ( const GLfloat s ) const {
        GLfloat r = 1.0f / s;
        return *this * r;
    }

    //
    //  --- (modifying) Arithematic Operators ---
    //

    vec2& operator += ( const vec2& v )
        { x += v.x;  y += v.y; return *this; }

    vec2& operator -= ( const vec2& v )
        { x -= v.x;  y -= v.y; return *this; }

    vec2& operator *= ( const GLfloat s )
        { x *= s;  y *= s; return *this; }

    vec2& operator *= ( const vec2& v )
        { x *= v.x;  y *= v.y; return *this; }

    vec2& operator /= ( const GLfloat s ) {
        GLfloat r = 1.0f / s;
        return *this *= r;
    }
        
    //
    //  --- Insertion and Extraction Operators ---
    //

    friend std::ostream& operator << ( std::ostream& os, const vec2& v ) {
        return os << "( " << v.x << ", " << v.y <<  " )";
    }

    friend std::istream& operator >> ( std::istream& is, vec2& v )
        { return is >> v.x >> v.y ; }

    //
    //  --- Conversion Operators ---
    //

    operator const GLfloat* () const
        { return static_cast<const GLfloat*>( &x ); }

    operator GLfloat* ()
        { return static_cast<GLfloat*>( &x ); }

    //
    //  --- Additional Methods ---
    //

    vec2 min( const vec2& v ) const
        { return vec2( std::min(x, v.x), std::min(y, v.y) ); }

    vec2 max( const vec2& v ) const
        { return vec2( std::max(x, v.x), std::max(y, v.y) ); }
};


//////////////////////////////////////////////////////////////////////////////
//
//  vec3 - 3D vector
//
//////////////////////////////////////////////////////////////////////////////

struct vec4;  // Forward declaration

struct vec3 {

    GLfloat  x;
    GLfloat  y;
    GLfloat  z;

    //
    //  --- Constructors and Destructors ---
    //

    vec3( const GLfloat s = 0.0f ) :
        x(s), y(s), z(s) {}

    vec3( const GLfloat x, const GLfloat y, const GLfloat z ) :
        x(x), y(y), z(z) {}
    
    vec3( const vec2& v, const GLfloat z = 0.0f ) :
        x(v.x), y(v.y), z(z) {}

    vec3( const vec4& v );
    //
    //  --- Indexing Operator ---
    //

    GLfloat& operator [] ( int i ) { return *(&x + i); }
    GLfloat operator [] ( int i ) const { return *(&x + i); }

    //
    //  --- Equality Operators ---
    //

    bool operator == ( const vec3& v )
        { return x == v.x && y == v.y && z == v.z; }

    bool operator != ( const vec3& v )
        { return x != v.x || y != v.y || z != v.z; }
    
    //
    //  --- (non-modifying) Arithematic Operators ---
    //

    vec3 operator - () const  // unary minus operator
        { return vec3( -x, -y, -z ); }

    vec3 operator + ( const vec3& v ) const
        { return vec3( x + v.x, y + v.y, z + v.z ); }

    vec3 operator - ( const vec3& v ) const
        { return vec3( x - v.x, y - v.y, z - v.z ); }

    vec3 operator * ( const GLfloat s ) const
        { return vec3( s*x, s*y, s*z ); }

    vec3 operator * ( const vec3& v ) const
        { return vec3( x*v.x, y*v.y, z*v.z ); }

    friend vec3 operator * ( const GLfloat s, const vec3& v )
        { return v * s; }

    vec3 operator / ( const GLfloat s ) const {
        GLfloat r = 1.0f / s;
        return *this * r;
    }

    //
    //  --- (modifying) Arithematic Operators ---
    //

    vec3& operator += ( const vec3& v )
        { x += v.x;  y += v.y;  z += v.z;  return *this; }

    vec3& operator -= ( const vec3& v )
        { x -= v.x;  y -= v.y;  z -= v.z;  return *this; }

    vec3& operator *= ( const GLfloat s )
        { x *= s;  y *= s;  z *= s;  return *this; }

    vec3& operator *= ( const vec3& v )
        { x *= v.x;  y *= v.y;  z *= v.z;  return *this; }

    vec3& operator /= ( const GLfloat s ) {
        GLfloat r = 1.0f / s;
        *this *= r;

        return *this;
    }
        
    //
    //  --- Insertion and Extraction Operators ---
    //

    friend std::ostream& operator << ( std::ostream& os, const vec3& v ) {
        return os << "( " << v.x << ", " << v.y << ", " << v.z <<  " )";
    }

    friend std::istream& operator >> ( std::istream& is, vec3& v )
        { return is >> v.x >> v.y >> v.z ; }

    //
    //  --- Conversion Operators ---
    //

    operator const GLfloat* () const
        { return static_cast<const GLfloat*>( &x ); }

    operator GLfloat* ()
        { return static_cast<GLfloat*>( &x ); }

    //
    //  --- Additional Methods ---
    //

    vec3 min( const vec3& v ) const
        { return vec3( std::min(x, v.x), std::min(y, v.y), std::min(z, v.z) ); }

    vec3 max( const vec3& v ) const
        { return vec3( std::max(x, v.x), std::max(y, v.y), std::max(z, v.z) ); }
};


//////////////////////////////////////////////////////////////////////////////
//
//  vec4 - 4D vector
//
//////////////////////////////////////////////////////////////////////////////

struct vec4 {

    GLfloat  x;
    GLfloat  y;
    GLfloat  z;
    GLfloat  w;

    //
    //  --- Constructors and Destructors ---
    //

    vec4( const GLfloat s = 0.0f ) :
        x(s), y(s), z(s), w(s) {}

    vec4( const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w ) :
        x(x), y(y), z(z), w(w) {}

    vec4( const vec3& v, const GLfloat w = 0.0f ) :
        x(v.x), y(v.y), z(v.z), w(w) {}

    vec4( const vec2& v, const GLfloat z = 0.0f, const GLfloat w = 0.0f ) :
        x(v.x), y(v.y), z(z), w(w) {}

    //
    //  --- Indexing Operator ---
    //

    GLfloat& operator [] ( int i ) { return *(&x + i); }
    GLfloat operator [] ( int i ) const { return *(&x + i); }

    //
    //  --- Equality Operators ---
    //

    bool operator == ( const vec4& v )
        { return x == v.x && y == v.y && z == v.z && w == v.w; }

    bool operator != ( const vec4& v )
        { return x != v.x || y != v.y || z != v.z || w != v.w; }
    
    //
    //  --- (non-modifying) Arithematic Operators ---
    //

    vec4 operator - () const  // unary minus operator
        { return vec4( -x, -y, -z, -w ); }

    vec4 operator + ( const vec4& v ) const
        { return vec4( x + v.x, y + v.y, z + v.z, w + v.w ); }

    vec4 operator - ( const vec4& v ) const
        { return vec4( x - v.x, y - v.y, z - v.z, w - v.w ); }

    vec4 operator * ( const GLfloat s ) const
        { return vec4( s*x, s*y, s*z, s*w ); }

    vec4 operator * ( const vec4& v ) const
        { return vec4( x*v.x, y*v.y, z*v.z, w*v.z ); }

    friend vec4 operator * ( const GLfloat s, const vec4& v )
        { return v * s; }

    vec4 operator / ( const GLfloat s ) const {
        GLfloat r = 1.0f / s;
        return *this * r;
    }

    //
    //  --- (modifying) Arithematic Operators ---
    //

    vec4& operator += ( const vec4& v )
        { x += v.x;  y += v.y;  z += v.z;  w += v.w;  return *this; }

    vec4& operator -= ( const vec4& v )
        { x -= v.x;  y -= v.y;  z -= v.z;  w -= v.w;  return *this; }

    vec4& operator *= ( const GLfloat s )
        { x *= s;  y *= s;  z *= s;  w *= s;  return *this; }

    vec4& operator *= ( const vec4& v )
        { x *= v.x, y *= v.y, z *= v.z, w *= v.w;  return *this; }

    vec4& operator /= ( const GLfloat s ) {
        GLfloat r = 1.0f / s;
        return *this *= r;
    }
        
    //
    //  --- Insertion and Extraction Operators ---
    //

    friend std::ostream& operator << ( std::ostream& os, const vec4& v ) {
        return os << "( " << v.x << ", " << v.y
                  << ", " << v.z << ", " << v.w << " )";
    }

    friend std::istream& operator >> ( std::istream& is, vec4& v )
        { return is >> v.x >> v.y >> v.z >> v.w; }

    //
    //  --- Conversion Operators ---
    //

    operator const GLfloat* () const
        { return static_cast<const GLfloat*>( &x ); }

    operator GLfloat* ()
        { return static_cast<GLfloat*>( &x ); }

    //
    //  --- Additional Methods ---
    //

    vec4 min( const vec4& v ) const {
        return vec4( std::min(x, v.x), std::min(y, v.y),
                     std::min(z, v.z), std::min(w, v.w) );
    }

    vec4 max( const vec4& v ) const {
        return vec4( std::max(x, v.x), std::max(y, v.y),
                     std::max(z, v.z), std::max(w, v.w) );
    }
};

//----------------------------------------------------------------------------
//
//  --- vec3 constructor ---
//

inline 
vec3::vec3( const vec4& v ) : x(v.x), y(v.y), z(v.z) {}

//----------------------------------------------------------------------------
//
//  --- Miscellaneous Functions ---
//

inline
GLfloat dot( const vec2& u, const vec2& v ) {
    return u.x * v.x + u.y * v.y;
}

inline
GLfloat dot( const vec3& u, const vec3& v ) {
    return u.x * v.x + u.y * v.y + u.z * v.z ;
}

inline
GLfloat dot( const vec4& u, const vec4& v ) {
    return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;
}

//----------------------------------------------------------------------------
//
//  Non-class Template Methods

template <typename T> inline
GLfloat length( const T& v ) {
    return std::sqrt( dot(v, v) );
}

template <typename T> inline
T normalize( const T& v ) {
    return v / length( v );
}

template <typename T> inline
vec3 cross( const T& u, const T& v ) {
    vec3 a( u );
    vec3 b( v );

    return vec3( a.y * b.z - a.z * b.y,
                 a.z * b.x - a.x * b.z,
                 a.x * b.y - a.y * b.x );
}

template <typename T> inline
T min( const T& u, const T& v ) {
    return u.min( v );    
}
    
template <typename T> inline
T max( const T& u, const T& v ) {
    return u.max( v );    
}
    

//----------------------------------------------------------------------------

}  // namespace Angel

#endif // __ANGEL_VEC_H__
