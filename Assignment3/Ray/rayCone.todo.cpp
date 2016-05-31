#include <math.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include "rayScene.h"
#include "rayCone.h"


////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RayCone::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
	return -1;
}

BoundingBox3D RayCone::setBoundingBox(void){
	Point3D p;
	p=Point3D(radius,height/2,radius);
	bBox=BoundingBox3D(center+p,center-p);
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RayCone::drawOpenGL(int materialIndex){
	int used_mt = materialIndex;
	if (materialIndex != material->index)
	{
		used_mt = material->index;
		material->drawOpenGL();
	}

	GLUquadricObj *quadric;
	quadric = gluNewQuadric();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(center[0], center[1], center[2]);
	glRotated(-90, 1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, -0.5*height);

	gluQuadricOrientation(quadric, GLU_OUTSIDE);
	gluCylinder(quadric, 0, radius, height, 100, 100);
	
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslated(0.0, 0.0, height);
		gluQuadricOrientation(quadric, GLU_OUTSIDE);
		gluDisk(quadric, 0, radius, 100, 100);
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();


	delete quadric;
	return used_mt;
}
