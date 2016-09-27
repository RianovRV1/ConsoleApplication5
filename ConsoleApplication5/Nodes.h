//////////////////////////////////////////////////////////////////////////////
//
//  --- Nodes.h ---
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __NODES_H__
#define __NODES_H__



#include <iostream>
#include <string>
#include <vector>
#include "Angel.h"
#include "BBox.h"


using namespace std;

namespace Scene {

//----------------------------------------------------------------------------
//
//  --- Node ---
//
///  @class Node
///  @brief Base class for all nodes stored in the scene graph

struct Traversal;  // Foward declaration of Traversal base class

struct Node {
    Node() {}
    virtual ~Node() {}

    virtual void receive( Traversal* ) = 0;
};

//----------------------------------------------------------------------------
//
// --- GeometricObject ---
//
///  @class GeometricObject
///  @brief Base class for all geomteric objects.
///  @details The GeometricObject class is an object for managing an OpenGL
///    object that uses vertex array objects (VAOs), vertex buffer objects
///    (VBOs), and shader programs.

struct GeometricObject : public Node {

    BBox     bbox;     /// geometry bounding box
    GLuint   vao;      /// vertex array object handle
    GLuint   vbo;      /// vertex buffer object handle
    GLsizei  numVertices;  /// number of vertices to be rendered
    GLuint   program;  /// Shader program handle
    GLint    uP;       /// Shader projection transformation uniform location
    GLint    uMV;      /// Shader model-view transformation uniform location

    GeometricObject( GLuint program ) :
        Node(), bbox(), numVertices(0), program(program)
        { _init(); }
                                        
    GeometricObject( const std::string& vertexShader = "C:\\Users\\Tanner\\Documents\\visual studio 2013\\Projects\\ConsoleApplication5\\ConsoleApplication5\\default.vert",
                     const std::string& fragmentShader = "C:\\Users\\Tanner\\Documents\\visual studio 2013\\Projects\\ConsoleApplication5\\ConsoleApplication5\\default.frag" ) :
        Node(), bbox(), numVertices(0)
        { 
            program = Angel::InitShader( vertexShader.c_str(),
                                         fragmentShader.c_str() );
            _init();
        }

    virtual ~GeometricObject() {
        glDeleteVertexArrays( 1, &vao );
        glDeleteBuffers( 1, &vbo );
        glDeleteProgram( program );
    }

    virtual void receive( Traversal* t );

  private:
    void _init() {
            glGenVertexArrays( 1, &vao );
            glBindVertexArray( vao );

            glGenBuffers( 1, &vbo );
            glBindBuffer( GL_ARRAY_BUFFER, vbo );

            uP = glGetUniformLocation( program, "P" );
            uMV = glGetUniformLocation( program, "MV" );
    }
};

//----------------------------------------------------------------------------
//
// --- Transform ---
//
///  @class Transform
///  @brief 
///  @details

struct Transform : public Node {

    typedef Angel::mat4         mat4;
    typedef std::vector<Node*>  Nodes;

    mat4   xform;
    Nodes  nodes;

    Transform() : xform(), nodes() {}
    ~Transform()
        { nodes.clear(); }
    
    void addNode( Node* n )
        { nodes.push_back( n ); }

    // Function implemented in Traversals.h
    virtual void receive( Traversal* );
};

    
//----------------------------------------------------------------------------

};  // namespace Scene

#endif // __NODES_H__
