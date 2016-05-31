#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include <math.h>
#include "rayCamera.h"



//////////////////
// OpenGL stuff //
//////////////////
void RayCamera::drawOpenGL(void){

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Point3D cen = position + direction * 100;

	gluLookAt(position[0], 
		position[1], 
		position[2], 
		cen[0], 
		cen[1], 
		cen[2], 
		up[0], 
		up[1], 
		up[2]);
}
void RayCamera::rotateUp(Point3D center,float angle){
	Matrix4D trans;

    Point3D  axis = direction.crossProduct(up).unit();

	double cos_theta = cos(angle);
	double sin_theta = sin(angle);

	trans(0,0) = cos_theta + (1 - cos_theta) * axis.p[0] * axis.p[0];
	trans(1,1) = cos_theta + (1 - cos_theta) * axis.p[1] * axis.p[1];
	trans(2,2) = cos_theta + (1 - cos_theta) * axis.p[2] * axis.p[2];

	trans(0,1) = (1 - cos_theta) * axis.p[0] * axis.p[1] - sin_theta * axis.p[2];
	trans(1,0) = (1 - cos_theta) * axis.p[0] * axis.p[1] + sin_theta * axis.p[2];

	trans(0,2) = (1 - cos_theta) * axis.p[0] * axis.p[2] + sin_theta * axis.p[1];
	trans(2,0) = (1 - cos_theta) * axis.p[0] * axis.p[2] - sin_theta * axis.p[1];

	trans(1,2) = (1 - cos_theta) * axis.p[1] * axis.p[2] - sin_theta * axis.p[0];
	trans(2,1) = (1 - cos_theta) * axis.p[1] * axis.p[2] + sin_theta * axis.p[0];


	Point3D tmp_pos = position - center;
	tmp_pos = trans.multPosition(tmp_pos);
	position = tmp_pos + center;

	direction = trans.multDirection(direction).unit();
	up = trans.multNormal(up).unit();
}

void RayCamera::rotateRight(Point3D center, float angle){
	Matrix4D trans;

    Point3D  axis = up;

	double cos_theta = cos(angle);
	double sin_theta = sin(angle);

	trans(0,0) = cos_theta + (1 - cos_theta) * axis.p[0] * axis.p[0];
	trans(1,1) = cos_theta + (1 - cos_theta) * axis.p[1] * axis.p[1];
	trans(2,2) = cos_theta + (1 - cos_theta) * axis.p[2] * axis.p[2];

	trans(0,1) = (1 - cos_theta) * axis.p[0] * axis.p[1] - sin_theta * axis.p[2];
	trans(1,0) = (1 - cos_theta) * axis.p[0] * axis.p[1] + sin_theta * axis.p[2];

	trans(0,2) = (1 - cos_theta) * axis.p[0] * axis.p[2] + sin_theta * axis.p[1];
	trans(2,0) = (1 - cos_theta) * axis.p[0] * axis.p[2] - sin_theta * axis.p[1];

	trans(1,2) = (1 - cos_theta) * axis.p[1] * axis.p[2] - sin_theta * axis.p[0];
	trans(2,1) = (1 - cos_theta) * axis.p[1] * axis.p[2] + sin_theta * axis.p[0];


	Point3D tmp_pos = position - center;
	tmp_pos = trans.multPosition(tmp_pos);
	position = tmp_pos + center;

	direction = trans.multDirection(direction).unit();
//	up = trans.multNormal(up).unit();

}
void RayCamera::moveForward(float dist){
}
void RayCamera::moveRight(float dist){
}
void RayCamera::moveUp(float dist){
}
