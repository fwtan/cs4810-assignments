#include <math.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include "rayScene.h"
#include "rayBox.h"
#include <vector>
using std::vector;

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RayBox::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
	return -1;
}
BoundingBox3D RayBox::setBoundingBox(void){
	bBox=BoundingBox3D(center-(length/2),center+(length/2));
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RayBox::drawOpenGL(int materialIndex)
{
	int used_mt = materialIndex;
	if (materialIndex != material->index)
	{
		used_mt = material->index;
		material->drawOpenGL();
	}

	Point3D radius = length * 0.5;

	const GLfloat faces[] = { 
		radius[0] + center[0], -radius[1] + center[1], -radius[2] + center[2],
		radius[0] + center[0],  radius[1] + center[1], -radius[2] + center[2],
		radius[0] + center[0],  radius[1] + center[1],  radius[2] + center[2],
		radius[0] + center[0], -radius[1] + center[1],  radius[2] + center[2],

		-radius[0] + center[0],  radius[1] + center[1], -radius[2] + center[2],
		-radius[0] + center[0], -radius[1] + center[1], -radius[2] + center[2],
		-radius[0] + center[0], -radius[1] + center[1],  radius[2] + center[2],
		-radius[0] + center[0],  radius[1] + center[1],  radius[2] + center[2],

		radius[0] + center[0],   radius[1] + center[1], -radius[2] + center[2],
		-radius[0] + center[0],  radius[1] + center[1], -radius[2] + center[2],
		-radius[0] + center[0],  radius[1] + center[1],  radius[2] + center[2],
		radius[0] + center[0],   radius[1] + center[1],  radius[2] + center[2],

		-radius[0] + center[0], -radius[1] + center[1], -radius[2] + center[2],
		radius[0] + center[0],  -radius[1] + center[1], -radius[2] + center[2],
		radius[0] + center[0],  -radius[1] + center[1],  radius[2] + center[2],
		-radius[0] + center[0], -radius[1] + center[1],  radius[2] + center[2],
		
		radius[0] + center[0],  -radius[1] + center[1],  radius[2] + center[2],
		radius[0] + center[0],   radius[1] + center[1],  radius[2] + center[2],
		-radius[0] + center[0],  radius[1] + center[1],  radius[2] + center[2],
		-radius[0] + center[0], -radius[1] + center[1],  radius[2] + center[2],

		radius[0] + center[0],   radius[1] + center[1],  -radius[2] + center[2],
		radius[0] + center[0],  -radius[1] + center[1],  -radius[2] + center[2],
		-radius[0] + center[0], -radius[1] + center[1],  -radius[2] + center[2],
		-radius[0] + center[0],  radius[1] + center[1],  -radius[2] + center[2]
		};

	const GLfloat normals[] = { 
		1.f, 0.f, 0.f, 
		-1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, -1.f, 0.f,
		0.f, 0.f, 1.f,
		0.f, 0.f, -1.f};

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	for (int i = 0; i < 6; i++) 
	{
	    glBegin(GL_QUADS);
		    glNormal3fv(normals+3*i);
		    glVertex3fv(faces+12*i+0);
		    glVertex3fv(faces+12*i+3);
		    glVertex3fv(faces+12*i+6);
		    glVertex3fv(faces+12*i+9);
	    glEnd();
  	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
	return used_mt;
}
