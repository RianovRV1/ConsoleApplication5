//////////////////////////////////////////////////////////////////////////////
//
//  --- Traversals.h ---
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __TRAVERSALS_H__
#define __TRAVERSALS_H__


#include "Nodes.h"
#include "Shapes.h"
#include "SceneGraph.h"

namespace Scene {

//----------------------------------------------------------------------------
//
//  --- Traversal ---
//
/// \class Traversal
/// \brief Base class of all traversals

struct GeometricObject;

struct Traversal {

    SceneGraph* scene;
    
    Traversal() {}
    virtual ~Traversal () {}

    virtual void traverse( SceneGraph* s ) {
        scene = s;
        for ( auto n : s->nodes ) {
            n->receive( this );
        }
    }

    // We need a visit method for every tupe of node we want to process
    virtual void visit( GeometricObject* ) {}
    virtual void visit( Cone* ) {}
    virtual void visit( GroundPlane* ) {}
	virtual void visit(Cube*) {}
	virtual void visit(Sphere*) {}
    virtual void visit( Transform* ) {}
	virtual void visit(SphereLines*) {}
	virtual void visit(LineQuad*) {}
};

void Cone::receive( Traversal* t ) { t->visit( this ); }
void GroundPlane::receive( Traversal* t ) { t->visit( this ); }
void Cube::receive( Traversal* t ) { t->visit(this); }
void Sphere::receive(Traversal* t) { t->visit(this); }
void SphereLines::receive(Traversal* t) { t->visit(this); }
void LineQuad::receive(Traversal* t) { t->visit(this); }
void GeometricObject::receive( Traversal* t ) { t->visit( this ); }
void Transform::receive( Traversal* t ) { t->visit( this ); }


//----------------------------------------------------------------------------
//
//  --- BoundingBox Traversal ---
//
/// \class BoundingBoxTraversal
/// \brief A traversal that will compute the bounding box of the entire scene

struct BoundingBoxTraversal : public Traversal {

    BBox  bbox;  /// Bounding box of entire scene

    virtual void visit( Cone* node )
        { bbox = bbox.merge( node->bbox ); }
    
	virtual void visit(GroundPlane* node)
	{
		bbox = bbox.merge(node->bbox);
	}
	virtual void visit(Sphere* node)
	{
		bbox = bbox.merge(node->bbox);
	}
	virtual void visit(SphereLines* node)
	{
		bbox = bbox.merge(node->bbox);
	}
	virtual void visit(LineQuad* node)
	{
		bbox = bbox.merge(node->bbox);
	}
    virtual void visit( GeometricObject* node )
        { bbox = bbox.merge( node->bbox ); }
	virtual void visit(Cube* node)
	{
		bbox = bbox.merge(node->bbox);
	}
    virtual void visit( Transform* node ) {
        for ( auto n : node->nodes ) {
            n->receive( this );
        }
    }
};

//----------------------------------------------------------------------------
//
//  --- Render Traversal ---
//
/// \class RenderTraversal
/// \brief A traversal that will render all of the nodes in the scene

struct RenderTraversal : public Traversal {

    typedef Angel::mat4  mat4;
    
    virtual void visit( Cone* node ) {
        glBindVertexArray( node->vao );
        glUseProgram( node->program );

        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

        glUniformMatrix4fv( node->uP, 1, GL_TRUE, scene->P );
        glUniformMatrix4fv( node->uMV, 1, GL_TRUE, scene->MV );
        
        glDrawArrays( GL_TRIANGLE_FAN, 0, node->numVertices );
        glDrawElements( GL_TRIANGLE_FAN, node->numConeVerties,
                        GL_UNSIGNED_INT, BUFFER_OFFSET(0) );

        size_t offset = node->numConeVerties * sizeof(GLuint);
        glDrawElements( GL_TRIANGLE_FAN, node->numBaseVertices,
                        GL_UNSIGNED_INT, BUFFER_OFFSET(offset) );
    }

    virtual void visit( GeometricObject* node ) {
        glBindVertexArray( node->vao );
        glUseProgram( node->program );

        glDrawArrays( GL_TRIANGLE_FAN, 0, node->numVertices );

        glUseProgram( 0 );
        glBindVertexArray( 0 );
    }
	virtual void visit(GroundPlane* node)
	{
		glBindVertexArray(node->vao);
		glUseProgram(node->program);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glUniformMatrix4fv(node->uP, 1, GL_TRUE, scene->P);
		glUniformMatrix4fv(node->uMV, 1, GL_TRUE, scene->MV);

		glDrawArrays(GL_TRIANGLE_FAN, 0, node->numVertices);	
	}
	virtual void visit(SphereLines* node)
	{
		glEnable(GL_BLEND);
		
		int start = 0;
		node->update(&start);
		node->update(&start);
		node->update(&start);
		node->update(&start);
		node->update(&start);
		glBindVertexArray(node->vao);
		glUseProgram(node->program);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glUniformMatrix4fv(node->uP, 1, GL_TRUE, scene->P);
		glUniformMatrix4fv(node->uMV, 1, GL_TRUE, scene->MV);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, node->numVertices);
		

		glDisable(GL_BLEND);
	}
	virtual void visit(LineQuad* node)
	{
		glBindVertexArray(node->vao);
		glUseProgram(node->program);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL
			);

		glUniformMatrix4fv(node->uP, 1, GL_TRUE, scene->P);
		glUniformMatrix4fv(node->uMV, 1, GL_TRUE, scene->MV);
	
		glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
		glVertexAttribDivisor(1, 1); // positions : one per quad (its center) -> 1
		glVertexAttribDivisor(2, 1); // color : one per quad -> 1

		// Draw the particules !
		// This draws many times a small triangle_strip (which looks like a quad).
		// This is equivalent to :
		// for(i in ParticlesCount) : glDrawArrays(GL_TRIANGLE_STRIP, 0, 4), 
		// but faster.
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, 10000);
		
		//glDrawArrays(GL_TRIANGLE_STRIP, 0, node->numVertices);
	}
	virtual void visit(Cube* node)
	{
		glBindVertexArray(node->vao);
		glUseProgram(node->program);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL
			);

		glUniformMatrix4fv(node->uP, 1, GL_TRUE, scene->P);
		glUniformMatrix4fv(node->uMV, 1, GL_TRUE, scene->MV);

		glDrawArrays(GL_TRIANGLES, 0, node->numVertices);
		
	}
	virtual void visit(Sphere* node)
	{
		glBindVertexArray(node->vao);
		glUseProgram(node->program);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glUniformMatrix4fv(node->uP, 1, GL_TRUE, scene->P);
		glUniformMatrix4fv(node->uMV, 1, GL_TRUE, scene->MV);
		
		glDrawArrays(GL_TRIANGLE_STRIP, 0, node->numVertices);
		
	}
    virtual void visit( Transform* transform ) {
        mat4 tmp = scene->MV;
        scene->MV *= transform->xform;
        for ( auto n : transform->nodes ) {
            n->receive( this );
        }
        scene->MV = tmp;
    }
};

//----------------------------------------------------------------------------

};  // namespace Scene

#endif // __TRAVERSALS_H__
