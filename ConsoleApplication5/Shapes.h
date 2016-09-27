//////////////////////////////////////////////////////////////////////////////
//
//  --- Shapes.h ---
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __SHAPES_H__
#define __SHAPES_H__

#include <iostream>
#include <string>
#include <vector>
#include "Angel.h"
#include "Nodes.h"
#include <cmath>
#include <SOIL.h>
#include <time.h>
#define Print(x)  cout << #x " = " << x << endl

using namespace std;

namespace Scene {

//----------------------------------------------------------------------------
//
//  --- GroundPlane ---
//
///  @class GroundPlane
///  @brief An xy-plane aligned for use as a the ground of a scene

struct GroundPlane : public GeometricObject {

    typedef Angel::vec2  vec2;
    typedef Angel::vec3  vec3;

    GroundPlane( const std::string& vs = "default.vert",
                 const std::string& fs = "default.frag" ) :
        GeometricObject( vs, fs ) {
        
        glBindVertexArray( vao );

        struct Vertex {
            vec2  pos;
        };
        
        std::vector<Vertex> vertices = {
            { vec2( -0.8, -0.8 ) },
            { vec2(  0.8, -0.8 ) },
            { vec2(  0.8,  0.8 ) },
            { vec2( -0.8,  0.8 ) }
        };

        numVertices = 0;
        for ( auto v : vertices ) {
            vec3 v3(v.pos);
			bbox.ll = vec3(-1.0, -1.0, 0.0);
			bbox.ur = vec3(1.0, 1.0, 1.0);
            //bbox.ll = Angel::min( bbox.ll, v3 );
           // bbox.ur = Angel::max( bbox.ur, v3 );
            numVertices++;
        }

        glBufferData( GL_ARRAY_BUFFER, numVertices * sizeof(Vertex),
                      &vertices[0], GL_STATIC_DRAW );

        GLint vPosition = glGetAttribLocation( program, "vPosition" );
        glVertexAttribPointer( vPosition, 2, GL_FLOAT, GL_FALSE,
                               sizeof(Vertex), BUFFER_OFFSET(0) );
        glEnableVertexAttribArray( vPosition );
    }

    // Function implemented in Traversals.h
    virtual void receive( Traversal* );
};

//----------------------------------------------------------------------------
//
//  --- Cone ---
//
///  @class Cone
///  @brief A cone with its base in the xy-plane, extruded up the z-axis

struct Cone : public GeometricObject {

    typedef Angel::vec3  vec3;

    GLuint   ebo;  /// vertex index buffer 
    GLsizei  numConeVerties;
    GLsizei  numBaseVertices;

    Cone( const GLsizei numSides = 10,
          const std::string& vs = "default.vert",
          const std::string& fs = "default.frag" ) :
        GeometricObject( vs, fs ) {

        glBindVertexArray( vao );

        typedef std::vector<vec3>  Vertices;
        typedef std::vector<GLuint>   Indices;
        
        Vertices vertices = {
            { vec3( 0.0, 0.0, 1.0 ) }  // apex vertex of the cone
        };


        Indices  indices;

        indices.push_back( 0 );  // Add apex vertex

        // Generate vertices around the cone's base
        float angle = 0.0, angleInc = 2.0*M_PI / numSides;
        for ( int i = 0; i < numSides; ++i, angle += angleInc ) {
            vec3 v( cos(angle), sin(angle), 0.0 );
            vertices.push_back( v );
            indices.push_back( i + 1 );
        }
        indices.push_back( 1 );  // add one more triangel to close shape
        numConeVerties = indices.size();

        // vertex for the middle of the cone's bottom
        vertices.push_back( vec3(0.0, 0.0, 0.0) );

        // Reuse vertices around cone's base to make its bottom
        indices.push_back( vertices.size() - 1 );
        for ( int i = 0; i < numSides; ++i ) {
            indices.push_back( i + 1 );
        }
        indices.push_back( 1 );  // add one more triangel to close shape

        numVertices = vertices.size();

        numBaseVertices = indices.size() - numConeVerties;

        // and since we know apropori the extents of the bounding box
        bbox.ll = vec3( -1.0, -1.0, 0.0 );
        bbox.ur = vec3(  1.0,  1.0, 1.0 );

        glBufferData( GL_ARRAY_BUFFER,
                      vertices.size() * sizeof(Vertices::value_type),
                      &vertices[0], GL_STATIC_DRAW );

        glGenBuffers( 1, &ebo );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER,
                      indices.size() * sizeof(Indices::value_type),
                      &indices[0], GL_STATIC_DRAW );
        
        GLint vPosition = glGetAttribLocation( program, "vPosition" );
        glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE,
                               sizeof(Vertices::value_type),
                               BUFFER_OFFSET(0) );
        glEnableVertexAttribArray( vPosition );
    }

    // Function implemented in Traversals.h
    virtual void receive( Traversal* );
};

struct Sphere : public GeometricObject
{
	typedef Angel::vec2  vec2;
	typedef Angel::vec3  vec3;
	int width, height, channels;
	
	GLubyte* pixels = SOIL_load_image("silver_texture.jpg", &width, &height,
		&channels, SOIL_LOAD_RGB);
	
	Sphere(const GLsizei Radius = 3, const std::string& vs = "default.vert",
		const std::string& fs = "default.frag") :
		GeometricObject(vs, fs) {
		struct Vertex {
			vec3 coordinates;
			vec2 texcoordinates;
		};
		
		double pi = M_PI;
		const int space = 6; // this can be constructor based
		const int VertexCount = (180 / space) * (360 / space) * 2;
		double h, k, z;
		h = 0;
		k = h;
		z = h;
		std::vector<Vertex> verts;
		double a, b;
		for (b = 0; b <= 180 - space; b += space)
		{
			srand(time(NULL));
			for (a = 0; a <= 360 - space; a += space)
			{
				
				float offset =  (rand() % 4) * 0.05;
				if (offset == 0)
					offset += 0.25;
				int choice = rand() % 2;
				if (choice == 0)
				{
					offset *= -1;
				}
				verts.push_back({ vec3((Radius-offset) * std::sin((a) / 180 * pi) * std::sin((b) / 180 * pi) - h,
					(Radius - offset) * std::cos((a) / 180 * pi) * std::sin((b) / 180 * pi) + k,
					(Radius - offset) * std::cos((b) / 180 * pi) - z),
					vec2(((a) / 360), ((2 * b) / 360) ) });
				
				verts.push_back({ vec3((Radius - offset) * std::sin((a) / 180 * pi) * std::sin((b + space) / 180 * pi) - h,
					(Radius - offset) * std::cos((a) / 180 * pi) * std::sin((b + space) / 180 * pi) + k,
					(Radius - offset) * std::cos((b + space) / 180 * pi) - z),
					vec2((a / 360), ((2 * (b + space)) / 360)) });

				/*verts.push_back({ vec3((Radius - offset) * std::sin((a + space) / 180 * pi) * std::sin((b) / 180 * pi) - h,
					(Radius - offset) * std::cos((a + space) / 180 * pi) * std::sin((b) / 180 * pi) + k,
					(Radius - offset) * std::cos((b) / 180 * pi) - z),
					vec2(((a + space) / 360), ((2 * b) / 360)) });

				verts.push_back({ vec3((Radius - offset) * std::sin((a + space) / 180 * pi) * std::sin((b + space) / 180 * pi) - h,
					(Radius - offset) * std::cos((a + space) / 180 * pi) * sin((b + space) / 180 * pi) + k,
					(Radius - offset) * std::cos((b + space) / 180 * pi) - z),
					vec2(((a + space) / 360), ((2 * (b + space)) / 360) ) });*/
			}
		}
		
		
	
		bbox.ll = vec3(-0.0, -0.0, -2.0);
		bbox.ur = vec3(0.0, 0.0, 20.0);
		numVertices = VertexCount;
		
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex),
			&verts[0], GL_STATIC_DRAW);
		
		
		GLint vPosition = 0;
		glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), BUFFER_OFFSET(0));
		glEnableVertexAttribArray(vPosition);
		
		GLint vTexCoord = 2;
		glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), BUFFER_OFFSET(sizeof(vec3)));
		glEnableVertexAttribArray(vTexCoord);

		glActiveTexture(GL_TEXTURE0);
		GLuint tex;
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
			GL_RGB, GL_UNSIGNED_BYTE, pixels);
		glUniform1i(tex, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		
	}
	virtual void receive(Traversal*);
};
//uses line quads, looks pretty neat
struct SphereLines : public GeometricObject
{
	typedef Angel::vec2  vec2;
	typedef Angel::vec3  vec3;
	typedef Angel::vec4  vec4;
	int width, height, channels;

	GLubyte* pixels = SOIL_load_image("Smoke.jpg", &width, &height, &channels, SOIL_LOAD_RGB);
	struct Vertex {
		vec3 coordinates;
		vec4 color;
		vec2 texture;

		Vertex(GLfloat coX, GLfloat coY, GLfloat coZ, GLfloat inX, GLfloat inY, GLfloat inZ, GLfloat inW, GLfloat texX, GLfloat texY)
		{
			coordinates = vec3(coX, coY, coZ);
			color = vec4(inX, inY, inZ, inW);
			texture = vec2(texX, texY);
		}

	};
	const int space = 6;
	const int VertexCount = (180 / space) * (360 / space) * 16;
	std::vector<Vertex> vectors;
	SphereLines(const GLsizei Radius = 5, const std::string& vs = "Line.vert",
		const std::string& fs = "Line.frag") :
		GeometricObject(vs, fs) {
		double h, k, z;
		h = 0;
		k = h;
		z = h;
		double pi = M_PI;
		double a, b;
		float yoffset = 0.2;
		for (b = 0; b <= 180 - space; b += space)
		{
			for (a = 0; a <= 360 - space; a += space)
			{

				vectors.push_back(Vertex(0, yoffset, 0, 0, 0, 0, 0, 0, 1));

				vectors.push_back(Vertex(Radius * std::sin((a) / 180 * pi) * std::sin((b) / 180 * pi) - h,
					Radius * std::cos((a) / 180 * pi) * std::sin((b) / 180 * pi) + (k+yoffset),
					Radius * std::cos((b) / 180 * pi) - z,
					0, 0, 0, 0, 1, 1));
				
				vectors.push_back(Vertex(0, -yoffset, 0, 0, 0, 0, 0, 0, 0));

				vectors.push_back(Vertex(Radius * std::sin((a) / 180 * pi) * std::sin((b) / 180 * pi) - h,
					Radius * std::cos((a) / 180 * pi) * std::sin((b) / 180 * pi) + (k - yoffset),
					Radius * std::cos((b) / 180 * pi) - z,
					0, 0, 0, 0, 1, 0));

				vectors.push_back(Vertex(0, yoffset, 0, 0, 0, 0, 0, 0, 1));

				vectors.push_back(Vertex(Radius * std::sin((a) / 180 * pi) * std::sin((b + space) / 180 * pi) - h,
					Radius * std::cos((a) / 180 * pi) * std::sin((b + space) / 180 * pi) + (k + yoffset),
					Radius * std::cos((b + space) / 180 * pi) - z,
					0, 0, 0, 0, 1, 1));
					
				vectors.push_back(Vertex(0, -yoffset, 0, 0, 0, 0, 0, 0, 0));

				vectors.push_back(Vertex(Radius * std::sin((a) / 180 * pi) * std::sin((b + space) / 180 * pi) - h,
					Radius * std::cos((a) / 180 * pi) * std::sin((b + space) / 180 * pi) + (k - yoffset),
					Radius * std::cos((b + space) / 180 * pi) - z,
					0, 0, 0, 0, 1, 0));

				vectors.push_back(Vertex(0, yoffset, 0, 0, 0, 0, 0, 0, 1));

				vectors.push_back(Vertex(Radius * std::sin((a + space) / 180 * pi) * std::sin((b) / 180 * pi) - h,
					Radius * std::cos((a + space) / 180 * pi) * std::sin((b) / 180 * pi) + (k + yoffset),
					Radius * std::cos((b) / 180 * pi) - z,
					0, 0, 0, 0, 1, 1));
				vectors.push_back(Vertex(0, -yoffset, 0, 0, 0, 0, 0, 0, 0));

				vectors.push_back(Vertex(Radius * std::sin((a + space) / 180 * pi) * std::sin((b) / 180 * pi) - h,
					Radius * std::cos((a + space) / 180 * pi) * std::sin((b) / 180 * pi) + (k - yoffset),
					Radius * std::cos((b) / 180 * pi) - z,
					0, 0, 0, 0, 1, 0));


				vectors.push_back(Vertex(0, yoffset, 0, 0, 0, 0, 0, 0, 1));

				vectors.push_back(Vertex(Radius * std::sin((a + space) / 180 * pi) * std::sin((b + space) / 180 * pi) - h,
					Radius * std::cos((a + space) / 180 * pi) * sin((b + space) / 180 * pi) + (k + yoffset),
					Radius * std::cos((b + space) / 180 * pi) - z,
					0, 0, 0, 0, 1, 1));
				vectors.push_back(Vertex(0, -yoffset, 0, 0, 0, 0, 0, 0, 0));

				vectors.push_back(Vertex(Radius * std::sin((a + space) / 180 * pi) * std::sin((b + space) / 180 * pi) - h,
					Radius * std::cos((a + space) / 180 * pi) * sin((b + space) / 180 * pi) + (k - yoffset),
					Radius * std::cos((b + space) / 180 * pi) - z,
					0, 0, 0, 0, 1, 0));
			}
		}
		
		bbox.ll = vec3(-0.0, -0.0, -0.0);
		bbox.ur = vec3(0.0, 0.0, 20.0);
		numVertices = VertexCount;



		GLint vPosition = 4;
		glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), BUFFER_OFFSET(0));
		glEnableVertexAttribArray(vPosition);

		GLint vColor = 1;
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), BUFFER_OFFSET(sizeof(vec3)));
		glEnableVertexAttribArray(vColor);


		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex),
			&vectors[0], GL_STATIC_DRAW);

		GLint vTexCoord = 3;
		glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), BUFFER_OFFSET(sizeof(vec3)*sizeof(vec4)));
		glEnableVertexAttribArray(vTexCoord);

		glActiveTexture(GL_TEXTURE1);
		GLuint tex;
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
			GL_RGB, GL_UNSIGNED_BYTE, pixels);
		glUniform1i(tex, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);



	}
	virtual void receive(Traversal*);

	int update(int* oldStart)
	{

		

		int choice = rand() % vectors.size();
		if ((choice % 4) == 1)
		{
			choice -= 1;
		}
		if ((choice % 4) == 2)
		{
			choice -= 2;
		}
		if ((choice % 4) == 3)
		{
			choice -= 3;
		}
		vectors[choice].color.w = 1;
		vectors[choice + 1].color.w = 1;
		vectors[choice + 2].color.w = 1;
		vectors[choice + 3].color.w = 1;


		int timestart = glutGet(GLUT_ELAPSED_TIME);
		int deltaTime = (timestart - *oldStart)*0.001;
		
		oldStart = &timestart;



		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex),
			&vectors[0], GL_STATIC_DRAW);

		for (int i = 0; i < vectors.size(); ++i)
		{
			vectors[i].color.w -= 0.01;
		}
		return deltaTime;

	}

};

//used to attempted instancing, failed horribly
struct LineQuad : public GeometricObject
{
	int width, height, channels;

	GLubyte* pixels = SOIL_load_image("Smoke.jpg", &width, &height,
		&channels, SOIL_LOAD_RGB);
	typedef Angel::vec4 vec4;
	typedef Angel::vec3 vec3;
	typedef Angel::vec2 vec2;
	LineQuad(const std::string& vs = "Line.vert",
	const std::string& fs = "Line.frag") :
	
	GeometricObject(vs, fs)
	{
		struct Vertex {
			vec3 coordinates;
			
			vec2 texcoordinates;
		};
		std::vector<Vertex> my_verts;
		std::vector<vec3> coordinates;
		std::vector<vec2> texcoord;
		my_verts.push_back({vec3(1, 0.2, 0.0), vec2(1, 0)});
		my_verts.push_back({ vec3(7, 0.2, 0.1),  vec2(1, 1) });
		my_verts.push_back({ vec3(1, -0.2, 0.0),  vec2(0, 0) });
		my_verts.push_back({ vec3(7, -0.2, 0.1),  vec2(0, 1) });
		bbox.ll = vec3(-0.0, -0.0, -2.0);
		bbox.ur = vec3(0.0, 0.0, 15.0);
		numVertices = my_verts.size();
		//here is some experimental instancing code

		GLuint billboard_vertex_buffer;
		glGenBuffers(1, &billboard_vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(my_verts), &my_verts[0], GL_STATIC_DRAW);

		// The VBO containing the positions and sizes of the particles
		GLuint particles_position_buffer;
		glGenBuffers(1, &particles_position_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
		// Initialize with empty (NULL) buffer : it will be updated later, each frame.
		glBufferData(GL_ARRAY_BUFFER, 10000 * 4 * sizeof(vec3), NULL, GL_STREAM_DRAW);

		// The VBO containing the colors of the particles
		GLuint particles_color_buffer;
		glGenBuffers(1, &particles_color_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
		// Initialize with empty (NULL) buffer : it will be updated later, each frame.
		glBufferData(GL_ARRAY_BUFFER, 10000 * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
		
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
		glVertexAttribPointer(
			0, // attribute. No particular reason for 0, but must match the layout in the shader.
			3, // size
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0, // stride
			(void*)0 // array buffer offset
			);

		// 2nd attribute buffer : positions of particles' centers
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
		glVertexAttribPointer(
			1, // attribute. No particular reason for 1, but must match the layout in the shader.
			4, // size : x + y + z + size => 4
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0, // stride
			(void*)0 // array buffer offset
			);

		// 3rd attribute buffer : particles' colors
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
		glVertexAttribPointer(
			2, // attribute. No particular reason for 1, but must match the layout in the shader.
			4, // size : r + g + b + a => 4
			GL_UNSIGNED_BYTE, // type
			GL_TRUE, // normalized? *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
			0, // stride
			(void*)0 // array buffer offset
			);

		//some seperation to seperate working code from experimental instancing code
		GLint vPosition = 4;
		glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), BUFFER_OFFSET(0));
		glEnableVertexAttribArray(vPosition);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex),
			&my_verts[0], GL_STATIC_DRAW);

		GLint vTexCoord = 3;
		glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), BUFFER_OFFSET(sizeof(vec3)));
		glEnableVertexAttribArray(vTexCoord);

		glActiveTexture(GL_TEXTURE0);
		GLuint tex;
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
			GL_RGB, GL_UNSIGNED_BYTE, pixels);
		glUniform1i(tex, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	virtual void receive(Traversal*);
};
struct Cube : public GeometricObject
{
	typedef Angel::vec2  vec2;
	typedef Angel::vec3  vec3;

	GLuint   ebo;  /// vertex index buffer 
	
	
	Cube(const int size = 4, const std::string& vs = "default.vert",
		const std::string& fs = "Square.frag") :
		GeometricObject(vs, fs) {
		struct Vertex {
			vec3  pos;
		}; //get pen and paper for these
		std::vector<Vertex> vertices = {
			//in order bottom: left, right, top: right, left
			//
			//back square 
			//first triangle
			{ vec3(-1.0, -1.0, -2.0) },
			{ vec3(-1.0, 1.0, -2.0) },
			{ vec3(1.0, -1.0, -2.0) },
			//second triangle 
			{ vec3(-1.0, 1.0, -2.0) },
			{ vec3(1.0, -1.0, -2.0) },
			{ vec3(1.0, 1.0, -2.0) },

			
			//top square
			{ vec3(-1.0, 1.0, -2.0) },
			{ vec3(-1.0, 1.0, 0.0) },
			{ vec3(1.0, 1.0, 0.0) },
			
			{ vec3(1.0, 1.0, 0.0) },
			{ vec3(1.0, 1.0, -2.0) },
			{ vec3(-1.0, 1.0, -2.0) },
			
			
			//left side square
			{ vec3(-1.0, 1.0, -2.0) },
			{ vec3(-1.0, -1.0, -2.0) },
			{ vec3(-1.0, -1.0, 0.0) },
			
			{ vec3(-1.0, -1.0, 0.0) },
			{ vec3(-1.0, 1.0, -2.0) },
			{ vec3(-1.0, 1.0, 0.0) },
		
			
			//front square
			{ vec3(-1.0, 1.0, 0.0) },
			{ vec3(-1.0, -1.0, 0.0) },
			{ vec3(1.0, 1.0, 0.0) },
			
			{ vec3(1.0, 1.0, 0.0) },
			{ vec3(1.0, -1.0, 0.0) },
			{ vec3(-1.0, -1.0, 0.0) },
			
			
			//botttom square
			{ vec3(1.0, -1.0, 0.0) },
			{ vec3(-1.0, -1.0, 0.0) },
			{ vec3(1.0, -1.0, -2.0) },
			
			{ vec3(-1.0, -1.0, -2.0) },
			{ vec3(-1.0, -1.0, 0.0) },
			{ vec3(1.0, -1.0, -2.0) },
			
	
			//right side square
			{ vec3(1.0, -1.0, -2.0) },
			{ vec3(1.0, -1.0, 0.0) },
			{ vec3(1.0, 1.0, 0.0) },
			
			{ vec3(1.0, 1.0, 0.0) },
			{ vec3(1.0, -1.0, -2.0) },
			{ vec3(1.0, 1.0, -2.0) }
			
		};
		
		static const GLfloat g_color_buffer_data[] = {
			0.583f, 0.771f, 0.014f,
			0.609f, 0.115f, 0.436f,
			0.327f, 0.483f, 0.844f,
			0.822f, 0.569f, 0.201f,
			0.435f, 0.602f, 0.223f,
			0.310f, 0.747f, 0.185f,
			0.597f, 0.770f, 0.761f,
			0.559f, 0.436f, 0.730f,
			0.359f, 0.583f, 0.152f,
			0.483f, 0.596f, 0.789f,
			0.559f, 0.861f, 0.639f,
			0.195f, 0.548f, 0.859f,
			0.014f, 0.184f, 0.576f,
			0.771f, 0.328f, 0.970f,
			0.406f, 0.615f, 0.116f,
			0.676f, 0.977f, 0.133f,
			0.971f, 0.572f, 0.833f,
			0.140f, 0.616f, 0.489f,
			0.997f, 0.513f, 0.064f,
			0.945f, 0.719f, 0.592f,
			0.543f, 0.021f, 0.978f,
			0.279f, 0.317f, 0.505f,
			0.167f, 0.620f, 0.077f,
			0.347f, 0.857f, 0.137f,
			0.055f, 0.953f, 0.042f,
			0.714f, 0.505f, 0.345f,
			0.783f, 0.290f, 0.734f,
			0.722f, 0.645f, 0.174f,
			0.302f, 0.455f, 0.848f,
			0.225f, 0.587f, 0.040f,
			0.517f, 0.713f, 0.338f,
			0.053f, 0.959f, 0.120f,
			0.393f, 0.621f, 0.362f,
			0.673f, 0.211f, 0.457f,
			0.820f, 0.883f, 0.371f,
			0.982f, 0.099f, 0.879f
		};
			bbox.ll = vec3(-0, -0, -4.0);
			bbox.ur = vec3(0.0, 0.0, 10.0);
		
		numVertices = vertices.size();

		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex),
			&vertices[0], GL_STATIC_DRAW);

		GLint vPosition = glGetAttribLocation(program, "vPosition");
		glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), BUFFER_OFFSET(0));
		glEnableVertexAttribArray(vPosition);
		
		GLuint colorbuffer;
		glGenBuffers(1, &colorbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
			);
		
	}
	virtual void receive(Traversal*);
};
//----------------------------------------------------------------------------

};  // namespace Scene

#endif // __SHAPES_H__
