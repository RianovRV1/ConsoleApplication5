//////////////////////////////////////////////////////////////////////////////
//
//  --- mat.h ---
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ANGEL_MAT_H__
#define __ANGEL_MAT_H__

#include <cmath>
#include "vec.h"

using std::cos;
using std::sin;
using std::tan;

namespace Angel {

//----------------------------------------------------------------------------
//
//  mat2 - 2D square matrix
//

class mat2 {

    vec2  _m[2];

   public:
    //
    //  --- Constructors and Destructors ---
    //

    mat2( const GLfloat d = 1.0f )  // Create a diagional matrix
        { _m[0].x = d;  _m[1].y = d; }

    mat2( const vec2& a, const vec2& b )
        { _m[0] = a;  _m[1] = b; }

    mat2( GLfloat m00, GLfloat m10, GLfloat m01, GLfloat m11 )
        { _m[0] = vec2( m00, m10 ); _m[1] = vec2( m01, m11 ); }

    //
    //  --- Indexing Operator ---
    //

    vec2& operator [] ( int i ) { return _m[i]; }
    const vec2& operator [] ( int i ) const { return _m[i]; }

    //
    //  --- Equality Operator ---
    //

    bool operator == ( const mat2& m )
        { return _m[0] == m[0] && _m[1] == m[1]; }

    bool operator != ( const mat2& m )
        { return _m[0] != m[0] || _m[1] != m[1]; }

    //
    //  --- (non-modifying) Arithmetic Operators ---
    //

    mat2 operator + ( const mat2& m ) const
        { return mat2( _m[0]+m[0], _m[1]+m[1] ); }

    mat2 operator - ( const mat2& m ) const
        { return mat2( _m[0]-m[0], _m[1]-m[1] ); }

    mat2 operator * ( const GLfloat s ) const 
        { return mat2( s*_m[0], s*_m[1] ); }

    mat2 operator / ( const GLfloat s ) const {
        GLfloat r = GLfloat(1.0) / s;
        return *this * r;
    }

    friend mat2 operator * ( const GLfloat s, const mat2& m )
        { return m * s; }
        
    mat2 operator * ( const mat2& m ) const {
        mat2  a( 0.0f );

        for ( int i = 0; i < 2; ++i ) {
            for ( int j = 0; j < 2; ++j ) {
                for ( int k = 0; k < 2; ++k ) {
                    a[i][j] += _m[i][k] * m[k][j];
                }
            }
        }

        return a;
    }

    //
    //  --- (modifying) Arithmetic Operators ---
    //

    mat2& operator += ( const mat2& m ) {
        _m[0] += m[0];  _m[1] += m[1];  
        return *this;
    }

    mat2& operator -= ( const mat2& m ) {
        _m[0] -= m[0];  _m[1] -= m[1];  
        return *this;
    }

    mat2& operator *= ( const GLfloat s ) {
        _m[0] *= s;  _m[1] *= s;   
        return *this;
    }

    mat2& operator *= ( const mat2& m ) {
        mat2  a( 0.0f );

        for ( int i = 0; i < 2; ++i ) {
            for ( int j = 0; j < 2; ++j ) {
                for ( int k = 0; k < 2; ++k ) {
                    a[i][j] += _m[i][k] * m[k][j];
                }
            }
        }

        return *this = a;
    }
    
    mat2& operator /= ( const GLfloat s ) {
        GLfloat r = 1.0f / s;
        return *this *= r;
    }

    //
    //  --- Matrix / Vector operators ---
    //

    vec2 operator * ( const vec2& v ) const {  // m * v
        return vec2( _m[0][0]*v.x + _m[0][1]*v.y,
                     _m[1][0]*v.x + _m[1][1]*v.y );
    }
        
    //
    //  --- Insertion and Extraction Operators ---
    //
        
    friend std::ostream& operator << ( std::ostream& os, const mat2& m )
        { return os << std::endl << m[0] << std::endl << m[1] << std::endl; }

    friend std::istream& operator >> ( std::istream& is, mat2& m )
        { return is >> m._m[0] >> m._m[1] ; }

    //
    //  --- Conversion Operators ---
    //

    operator const GLfloat* () const
        { return static_cast<const GLfloat*>( &_m[0].x ); }

    operator GLfloat* ()
        { return static_cast<GLfloat*>( &_m[0].x ); }
};

//
//  --- Non-class mat2 Methods ---
//

inline
mat2 matrixCompMult( const mat2& A, const mat2& B ) {
    return mat2( A[0][0]*B[0][0], A[0][1]*B[0][1],
                 A[1][0]*B[1][0], A[1][1]*B[1][1] );
}

inline
mat2 transpose( const mat2& A ) {
    return mat2( A[0][0], A[1][0],
                 A[0][1], A[1][1] );
}

//----------------------------------------------------------------------------
//
//  mat3 - 3D square matrix 
//

class mat3 {

    vec3  _m[3];

   public:
    //
    //  --- Constructors and Destructors ---
    //

    mat3( const GLfloat d = 1.0f )  // Create a diagional matrix
        { _m[0].x = d;  _m[1].y = d;  _m[2].z = d; }

    mat3( const vec3& a, const vec3& b, const vec3& c )
        { _m[0] = a;  _m[1] = b;  _m[2] = c; }

    mat3( GLfloat m00, GLfloat m10, GLfloat m20,
          GLfloat m01, GLfloat m11, GLfloat m21,
          GLfloat m02, GLfloat m12, GLfloat m22 )
        {
            _m[0] = vec3( m00, m10, m20 );
            _m[1] = vec3( m01, m11, m21 );
            _m[2] = vec3( m02, m12, m22 );
        }

    //
    //  --- Indexing Operator ---
    //

    vec3& operator [] ( int i ) { return _m[i]; }
    const vec3& operator [] ( int i ) const { return _m[i]; }

    //
    //  --- Equality Operator ---
    //

    bool operator == ( const mat3& m )
        { return _m[0] == m[0] && _m[1] == m[1] && _m[2] == m[2]; }

    bool operator != ( const mat3& m )
        { return _m[0] != m[0] || _m[1] != m[1] || _m[2] != m[2]; }

    //
    //  --- (non-modifying) Arithmatic Operators ---
    //

    mat3 operator + ( const mat3& m ) const
        { return mat3( _m[0]+m[0], _m[1]+m[1], _m[2]+m[2] ); }

    mat3 operator - ( const mat3& m ) const
        { return mat3( _m[0]-m[0], _m[1]-m[1], _m[2]-m[2] ); }

    mat3 operator * ( const GLfloat s ) const 
        { return mat3( s*_m[0], s*_m[1], s*_m[2] ); }

    mat3 operator / ( const GLfloat s ) const {
        GLfloat r = 1.0f / s;
        return *this * r;
    }

    friend mat3 operator * ( const GLfloat s, const mat3& m )
        { return m * s; }
        
    mat3 operator * ( const mat3& m ) const {
        mat3  a( 0.0f );

        for ( int i = 0; i < 3; ++i ) {
            for ( int j = 0; j < 3; ++j ) {
                for ( int k = 0; k < 3; ++k ) {
                    a[i][j] += _m[i][k] * m[k][j];
                }
            }
        }

        return a;
    }

    //
    //  --- (modifying) Arithmetic Operators ---
    //

    mat3& operator += ( const mat3& m ) {
        _m[0] += m[0];  _m[1] += m[1];  _m[2] += m[2]; 
        return *this;
    }

    mat3& operator -= ( const mat3& m ) {
        _m[0] -= m[0];  _m[1] -= m[1];  _m[2] -= m[2]; 
        return *this;
    }

    mat3& operator *= ( const GLfloat s ) {
        _m[0] *= s;  _m[1] *= s;  _m[2] *= s; 
        return *this;
    }

    mat3& operator *= ( const mat3& m ) {
        mat3  a( 0.0f );

        for ( int i = 0; i < 3; ++i ) {
            for ( int j = 0; j < 3; ++j ) {
                for ( int k = 0; k < 3; ++k ) {
                    a[i][j] += _m[i][k] * m[k][j];
                }
            }
        }

        return *this = a;
    }

    mat3& operator /= ( const GLfloat s ) {
        GLfloat r = 1.0f / s;
        return *this *= r;
    }

    //
    //  --- Matrix / Vector operators ---
    //

    vec3 operator * ( const vec3& v ) const {  // m * v
        return vec3( _m[0][0]*v.x + _m[0][1]*v.y + _m[0][2]*v.z,
                     _m[1][0]*v.x + _m[1][1]*v.y + _m[1][2]*v.z,
                     _m[2][0]*v.x + _m[2][1]*v.y + _m[2][2]*v.z );
    }
        
    //
    //  --- Insertion and Extraction Operators ---
    //
        
    friend std::ostream& operator << ( std::ostream& os, const mat3& m ) {
        return os << std::endl 
                  << m[0] << std::endl
                  << m[1] << std::endl
                  << m[2] << std::endl;
    }

    friend std::istream& operator >> ( std::istream& is, mat3& m )
        { return is >> m._m[0] >> m._m[1] >> m._m[2] ; }

    //
    //  --- Conversion Operators ---
    //

    operator const GLfloat* () const
        { return static_cast<const GLfloat*>( &_m[0].x ); }

    operator GLfloat* ()
        { return static_cast<GLfloat*>( &_m[0].x ); }
};

//
//  --- Non-class mat3 Methods ---
//

inline
mat3 matrixCompMult( const mat3& A, const mat3& B ) {
    return mat3( A[0][0]*B[0][0], A[0][1]*B[0][1], A[0][2]*B[0][2],
                 A[1][0]*B[1][0], A[1][1]*B[1][1], A[1][2]*B[1][2],
                 A[2][0]*B[2][0], A[2][1]*B[2][1], A[2][2]*B[2][2] );
}

inline
mat3 transpose( const mat3& A ) {
    return mat3( A[0][0], A[1][0], A[2][0],
                 A[0][1], A[1][1], A[2][1],
                 A[0][2], A[1][2], A[2][2] );
}

//----------------------------------------------------------------------------
//
//  mat4.h - 4D square matrix
//

class mat4 {

    vec4  _m[4];

   public:
    //
    //  --- Constructors and Destructors ---
    //

    mat4( const GLfloat d = 1.0f )  // Create a diagional matrix
        { _m[0].x = d;  _m[1].y = d;  _m[2].z = d;  _m[3].w = d; }

    mat4( const vec4& a, const vec4& b, const vec4& c, const vec4& d )
        { _m[0] = a;  _m[1] = b;  _m[2] = c;  _m[3] = d; }

    mat4( GLfloat m00, GLfloat m10, GLfloat m20, GLfloat m30,
          GLfloat m01, GLfloat m11, GLfloat m21, GLfloat m31,
          GLfloat m02, GLfloat m12, GLfloat m22, GLfloat m32,
          GLfloat m03, GLfloat m13, GLfloat m23, GLfloat m33 )
        {
            _m[0] = vec4( m00, m10, m20, m30 );
            _m[1] = vec4( m01, m11, m21, m31 );
            _m[2] = vec4( m02, m12, m22, m32 );
            _m[3] = vec4( m03, m13, m23, m33 );
        }

    //
    //  --- Indexing Operator ---
    //

    vec4& operator [] ( int i ) { return _m[i]; }
    const vec4& operator [] ( int i ) const { return _m[i]; }

    //
    //  --- Equality Operator ---
    //

    bool operator == ( const mat4& m ) {
        return ( _m[0] == m[0] && _m[1] == m[1] &&
                 _m[2] == m[2] && _m[3] == m[3] );
    }

    bool operator != ( const mat4& m ) {
        return ( _m[0] != m[0] || _m[1] != m[1] ||
                 _m[2] != m[2] || _m[3] != m[3] );
    }

    //
    //  --- (non-modifying) Arithematic Operators ---
    //

    mat4 operator + ( const mat4& m ) const
        { return mat4( _m[0]+m[0], _m[1]+m[1], _m[2]+m[2], _m[3]+m[3] ); }

    mat4 operator - ( const mat4& m ) const
        { return mat4( _m[0]-m[0], _m[1]-m[1], _m[2]-m[2], _m[3]-m[3] ); }

    mat4 operator * ( const GLfloat s ) const 
        { return mat4( s*_m[0], s*_m[1], s*_m[2], s*_m[3] ); }

    mat4 operator / ( const GLfloat s ) const {
        GLfloat r = 1.0f / s;
        return *this * r;
    }

    friend mat4 operator * ( const GLfloat s, const mat4& m )
        { return m * s; }
        
    mat4 operator * ( const mat4& m ) const {
        mat4  a( 0.0f );

        for ( int i = 0; i < 4; ++i ) {
            for ( int j = 0; j < 4; ++j ) {
                for ( int k = 0; k < 4; ++k ) {
                    a[i][j] += _m[i][k] * m[k][j];
                }
            }
        }

        return a;
    }

    //
    //  --- (modifying) Arithematic Operators ---
    //

    mat4& operator += ( const mat4& m ) {
        _m[0] += m[0];  _m[1] += m[1];  _m[2] += m[2];  _m[3] += m[3];
        return *this;
    }

    mat4& operator -= ( const mat4& m ) {
        _m[0] -= m[0];  _m[1] -= m[1];  _m[2] -= m[2];  _m[3] -= m[3];
        return *this;
    }

    mat4& operator *= ( const GLfloat s ) {
        _m[0] *= s;  _m[1] *= s;  _m[2] *= s;  _m[3] *= s;
        return *this;
    }

    mat4& operator *= ( const mat4& m ) {
        mat4  a( 0.0f );

        for ( int i = 0; i < 4; ++i ) {
            for ( int j = 0; j < 4; ++j ) {
                for ( int k = 0; k < 4; ++k ) {
                    a[i][j] += _m[i][k] * m[k][j];
                }
            }
        }

        return *this = a;
    }

    mat4& operator /= ( const GLfloat s ) {
        GLfloat r = 1.0f / s;
        return *this *= r;
    }

    //
    //  --- Matrix / Vector operators ---
    //

    vec4 operator * ( const vec4& v ) const {  // m * v
        return vec4( _m[0][0]*v.x + _m[0][1]*v.y + _m[0][2]*v.z + _m[0][3]*v.w,
                     _m[1][0]*v.x + _m[1][1]*v.y + _m[1][2]*v.z + _m[1][3]*v.w,
                     _m[2][0]*v.x + _m[2][1]*v.y + _m[2][2]*v.z + _m[2][3]*v.w,
                     _m[3][0]*v.x + _m[3][1]*v.y + _m[3][2]*v.z + _m[3][3]*v.w
            );
    }
        
    //
    //  --- Insertion and Extraction Operators ---
    //
        
    friend std::ostream& operator << ( std::ostream& os, const mat4& m ) {
        return os << std::endl 
                  << m[0] << std::endl
                  << m[1] << std::endl
                  << m[2] << std::endl
                  << m[3] << std::endl;
    }

    friend std::istream& operator >> ( std::istream& is, mat4& m )
        { return is >> m._m[0] >> m._m[1] >> m._m[2] >> m._m[3]; }

    //
    //  --- Conversion Operators ---
    //

    operator const GLfloat* () const
        { return static_cast<const GLfloat*>( &_m[0].x ); }

    operator GLfloat* ()
        { return static_cast<GLfloat*>( &_m[0].x ); }
};

//
//  --- Non-class mat4 Methods ---
//

inline
mat4 matrixCompMult( const mat4& A, const mat4& B ) {
    return mat4(
        A[0][0]*B[0][0], A[0][1]*B[0][1], A[0][2]*B[0][2], A[0][3]*B[0][3],
        A[1][0]*B[1][0], A[1][1]*B[1][1], A[1][2]*B[1][2], A[1][3]*B[1][3],
        A[2][0]*B[2][0], A[2][1]*B[2][1], A[2][2]*B[2][2], A[2][3]*B[2][3],
        A[3][0]*B[3][0], A[3][1]*B[3][1], A[3][2]*B[3][2], A[3][3]*B[3][3] );
}

inline
mat4 transpose( const mat4& A ) {
    return mat4( A[0][0], A[1][0], A[2][0], A[3][0],
                 A[0][1], A[1][1], A[2][1], A[3][1],
                 A[0][2], A[1][2], A[2][2], A[3][2],
                 A[0][3], A[1][3], A[2][3], A[3][3] );
}

//////////////////////////////////////////////////////////////////////////////
//
//  Helpful Matrix Methods
//
//////////////////////////////////////////////////////////////////////////////
    
//----------------------------------------------------------------------------
//
//  Rotation matrix generators
//

inline
mat4 RotateX( const GLfloat theta )
{
    GLfloat angle = DegreesToRadians * theta;
    GLfloat c = cos(angle);
    GLfloat s = sin(angle);

    mat4 m;
    
    m[1][1] =  c;
    m[1][2] = -s;
    m[2][2] =  c;
    m[2][1] =  s;
    
    return m;
}

inline
mat4 RotateY( const GLfloat theta )
{
    GLfloat angle = DegreesToRadians * theta;
    GLfloat c = cos(angle);
    GLfloat s = sin(angle);
    
    mat4 m;
    
    m[0][0] =  c;
    m[0][2] =  s;
    m[2][2] =  c;
    m[2][0] = -s;
    
    return m;
}

inline
mat4 RotateZ( const GLfloat theta )
{
    GLfloat angle = DegreesToRadians * theta;
    GLfloat c = cos(angle);
    GLfloat s = sin(angle);
    
    mat4 m;

    m[0][0] =  c;
    m[1][1] =  c;
    m[1][0] =  s;
    m[0][1] = -s;
    
    return m;
}

 inline
 mat4 Rotate( const GLfloat theta, const vec3& axis )
 {
     GLfloat angle = DegreesToRadians * theta;
     
     vec3 u = normalize(axis);
     mat3 S(  0.0f, -u.z,  u.y,
              u.z,   0.0f, -u.x,
             -u.y,   u.x,   0.0f );
     
     mat3 utu( u.x * u.x, u.x * u.y, u.x * u.z,
               u.y * u.x, u.y * u.y, u.y * u.z,
               u.z * u.x, u.z * u.y, u.z * u.z );
     mat3 I;
     mat3 M = utu + cos(angle)*(I - utu) + sin(angle)*S;
     
     return mat4( vec4(M[0], 0.0f),
                  vec4(M[1], 0.0f),
                  vec4(M[2], 0.0f),
                  vec4(0.0f, 0.0f, 0.0f, 1.0f) );
 }

//----------------------------------------------------------------------------
//
//  Translation matrix generators
//

inline
mat4 Translate( const GLfloat x, const GLfloat y, const GLfloat z )
{
    mat4 m;
    m[0][3] = x;
    m[1][3] = y;
    m[2][3] = z;
    return m;
}

inline
mat4 Translate( const vec3& v )
{
    return Translate( v.x, v.y, v.z );
}

inline
mat4 Translate( const vec4& v )
{
    return Translate( v.x, v.y, v.z );
}

//----------------------------------------------------------------------------
//
//  Scale matrix generators
//

inline
mat4 Scale( const GLfloat x, const GLfloat y, const GLfloat z )
{
    mat4 m;
    m[0][0] = x;
    m[1][1] = y;
    m[2][2] = z;
    return m;
}

inline
mat4 Scale( const vec3& v )
{
    return Scale( v.x, v.y, v.z );
}

//----------------------------------------------------------------------------
//
//  Projection transformation matrix geneartors
//
//    Note: Microsoft Windows (r) defines the keyword "far" in C/C++.  In
//          order to avoid any name conflicts, we use the variable names
//          "zNear" to reprsent "near", and "zFar" to reprsent "far".
//



inline
mat4 Ortho( const GLfloat left, const GLfloat right,
            const GLfloat bottom, const GLfloat top,
            const GLfloat zNear, const GLfloat zFar )
{
    mat4 m;
    m[0][0] = 2.0f/(right - left);
    m[0][3] = -(right + left)/(right - left);
    m[1][1] = 2.0f/(top - bottom);
    m[1][3] = -(top + bottom)/(top - bottom);
    m[2][2] = 2.0f/(zNear - zFar);
    m[2][3] = -(zFar + zNear)/(zFar - zNear);
    m[3][3] = 1.0f;
    return m;
}

inline
mat4 Ortho2D( const GLfloat left, const GLfloat right,
              const GLfloat bottom, const GLfloat top )
{
    return Ortho( left, right, bottom, top, -1.0f, 1.0f );
}

inline
mat4 Frustum( const GLfloat left, const GLfloat right,
              const GLfloat bottom, const GLfloat top,
              const GLfloat zNear, const GLfloat zFar )
{
    mat4 m;
    m[0][0] = 2.0f*zNear/(right - left);
    m[0][2] = (right + left)/(right - left);
    m[1][1] = 2.0f*zNear/(top - bottom);
    m[1][2] = (top + bottom)/(top - bottom);
    m[2][2] = -(zFar + zNear)/(zFar - zNear);
    m[2][3] = -2.0f*zFar*zNear/(zFar - zNear);
    m[3][2] = -1.0f;
    m[3][3] =  0.0f;
    return m;
}

inline
mat4 Perspective( const GLfloat fovy, const GLfloat aspect,
                  const GLfloat zNear, const GLfloat zFar)
{
    GLfloat top   = tan(fovy*DegreesToRadians/2) * zNear;
    GLfloat right = top * aspect;

    mat4 m;
    m[0][0] = zNear/right;
    m[1][1] = zNear/top;
    m[2][2] = -(zFar + zNear)/(zFar - zNear);
    m[2][3] = -2.0f*zFar*zNear/(zFar - zNear);
    m[3][2] = -1.0f;
    m[3][3] = 0.0f;
    return m;
}

//----------------------------------------------------------------------------
//
//  Viewing transformation matrix generation
//

inline
mat4 LookAt( const vec4& eye, const vec4& at, const vec4& up )
{
    vec4 n = normalize( eye - at );
    vec4 u = vec4( normalize(cross(up,n)), 0.0f );
    vec4 v = vec4( normalize(cross(n,u)), 0.0f );
    vec4 t = vec4( 0.0f, 0.0f, 0.0f, 1.0f );
    mat4 m = mat4( u, v, n, t );
    return m * Translate( -eye );
}

//----------------------------------------------------------------------------
//
// Generates a Normal Matrix
//
inline
mat3 Normal( const mat4& c )
{
   GLfloat det = (  c[0][0]*c[1][1]*c[2][2]
                  + c[0][1]*c[1][2]*c[2][1]
                  + c[0][2]*c[1][0]*c[2][1]
                  - c[2][0]*c[1][1]*c[0][2]
                  - c[1][0]*c[0][1]*c[2][2]
                  - c[0][0]*c[1][2]*c[2][1] );
   mat3 m;
   
   m[0][0] =  (c[1][1]*c[2][2]-c[1][2]*c[2][1])/det;
   m[0][1] = -(c[1][0]*c[2][2]-c[1][2]*c[2][0])/det;
   m[0][2] =  (c[1][0]*c[2][1]-c[1][1]*c[2][0])/det;
   m[1][0] = -(c[0][1]*c[2][2]-c[0][2]*c[2][1])/det;
   m[1][1] =  (c[0][0]*c[2][2]-c[0][2]*c[2][0])/det;
   m[1][2] = -(c[0][0]*c[2][1]-c[0][1]*c[2][0])/det;
   m[2][0] =  (c[0][1]*c[1][2]-c[0][2]*c[1][1])/det;
   m[2][1] = -(c[0][0]*c[1][2]-c[0][2]*c[1][0])/det;
   m[2][2] =  (c[0][0]*c[1][1]-c[1][0]*c[0][1])/det;

  return m;
}

//----------------------------------------------------------------------------

}  // namespace Angel

#endif // __ANGEL_MAT_H__
