
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <cmath>

using std::cos;
using std::sin;

#include "Angel.h"
#include "Scene.h"

using namespace std;
using namespace Angel;
using namespace Scene;

SceneGraph*  scene;
Transform*   xform;

GLfloat  fovy = 80.0;
GLfloat zNear = 1.0;
GLfloat zFar;
vec3    center;
Angel::mat4 polarview(GLfloat dist, GLfloat elev,GLfloat azim, GLfloat twist)
{
	Angel::mat4 m ;
	m = Angel::Translate(vec3(0, 0, -dist));
	m *= Angel::RotateZ(-twist);
	m *= Angel::RotateX(-elev);
	m *= Angel::RotateZ(azim);
	return m;
}

void special(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		//x -= dx;
		break;
	case GLUT_KEY_RIGHT:
		//x += dx;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y)
{
	exit(EXIT_SUCCESS);
}
void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    scene = new SceneGraph();
	
    xform = new Transform();
    scene->addNode( xform );
	//xform->addNode(new GroundPlane());
	//xform->addNode(new Cube());
	
	xform->addNode(new Sphere(3));
	xform->addNode(new SphereLines(15));
	//xform->addNode(new LineQuad());
	
	//xform->addNode(new Sphere(3));
	//xform->addNode( new Cone(100) );
	
    BoundingBoxTraversal bbox;
    bbox.traverse( scene );

    center = -bbox.bbox.center();
    center.z -= 0.5 * bbox.bbox.diameter();
    zFar = zNear + bbox.bbox.diameter();
}


void display()
{
	
	glClear( GL_COLOR_BUFFER_BIT );
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    RenderTraversal render;
    render.traverse( scene );
    
    glutSwapBuffers();
}

void reshape( int width, int height )
{
	
	glViewport( 0, 0, width, height );

    GLfloat aspect = GLfloat(width)/height;
    
    scene->P = Perspective( fovy, aspect, zNear, zFar );
    scene->MV = Translate( center );
	
    glutPostRedisplay();
}



void idle( void )
{
	
	static GLfloat angle = 0.0;
	GLfloat angle2 = 0.5;
	bool rotatevert;
	bool rotatehorz;
	if (std::abs(angle) < 90)
	{
		rotatevert = false;
		rotatehorz = false;
	}
	else if (std::abs(angle) >= 90 && std::abs(angle) < 180)
	{
		rotatevert = true;
		rotatehorz = false;
	}
	else if (std::abs(angle) >= 180 && std::abs(angle) < 270)
	{
		rotatevert = true;
		rotatehorz = true;
	}
	else
	{
		angle = 0;
		rotatevert = false;
		rotatehorz = false;
	}
	mat4 change;
	
	if (rotatevert == false && rotatehorz == false)
	{
		angle -= 0.5;
		
		change *= Rotate(angle2, vec3(0, 1, 0));
	}
	else if (rotatevert == true && rotatehorz == false)
	{
		angle -= 0.5;
		change *= Rotate(angle2, vec3(1, 0, 0));
	}
	else if (rotatevert == true && rotatehorz == true)
	{
		angle -= 0.5;
		change *= Rotate(angle2, vec3(0, 1, 1));
	}
	xform->xform *= change;
	
    glutPostRedisplay();
}


int main( int argc, CHAR* argv[] )
{
	//srand(time(NULL));
	int width, height, channels;
	glewExperimental = GL_TRUE;
	glutInit( &argc, argv );
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE );
	glutInitContextVersion(4, 0);//actual GL features you need to add to the beginning of every main function
	glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow( "A Thing" );
	glewInit();
    init();
	
    glutIdleFunc( idle );
    glutKeyboardFunc( keyboard );
    glutReshapeFunc( reshape );
    glutDisplayFunc( display );
    
    glutMainLoop();
	system("PAUSE");
    return 0;
}
