//////////////////////////////////////////////////////////////////////////////
//
//  --- CheckError.h ---
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __CHECKERROR_H__
#define __CHECKERROR_H__

#include <stdio.h>

//#ifndef __ANGEL_H__
//#  if defined(__APPLE__) || defined(MACOSX)
//// #    define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
//#    include <OpenGL/gl.h>
//#    include <OpenGL/gl3.h>
//#  else
//#    include <GL/gl.h>
//#  endif
//#endif

//----------------------------------------------------------------------------

static const char*
ErrorString( GLenum error )
{
    const char*  msg;
    switch( error ) {
#define Case( Token )  case Token: msg = #Token; break
        Case( GL_INVALID_VALUE );
        Case( GL_NO_ERROR );
        Case( GL_INVALID_ENUM );
        Case( GL_INVALID_OPERATION );
        Case( GL_STACK_OVERFLOW );
        Case( GL_STACK_UNDERFLOW );
        Case( GL_OUT_OF_MEMORY );
#undef Case
        default:
            msg = "Unknown OpenGL error code.";
            break;
    }

    return msg;
}

//----------------------------------------------------------------------------

static void
_CheckError( const char* file, int line )
{
    GLenum  error = glGetError();

    do {
        fprintf( stderr, "[%s:%d] %s\n", file, line, ErrorString(error) );
    } while ((error = glGetError()) != GL_NO_ERROR );
        
}

//----------------------------------------------------------------------------

#define CheckError()  _CheckError( __FILE__, __LINE__ )

//----------------------------------------------------------------------------

#endif // !__CHECKERROR_H__
