#include <math.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include "rayScene.h"
#include "raySpotLight.h"


////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RaySpotLight::getDiffuse(Point3D cameraPosition,RayIntersectionInfo& iInfo)
{
	Point3D L = location - iInfo.iCoordinate;
	double d = L.length();
	L = L / d;

	Point3D dir = -direction / direction.length();
	double cos_gamma = dir.dot(L);
	double cos_theta = iInfo.normal.dot(dir);
	
	if (cos_theta <= 0)
	{
		return Point3D();
	}
	if (cos_gamma < cos(cutOffAngle))
	{
		return Point3D();
	}

	Point3D IL = color * pow(cos_gamma, dropOffRate) / (constAtten + linearAtten * d + quadAtten * d * d);
	Point3D Kd = iInfo.material->diffuse;

	return Kd.mult(IL * cos_theta);
}

Point3D RaySpotLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	return Point3D();
}
int RaySpotLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
	return 0;
}
Point3D RaySpotLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){
	return Point3D(1,1,1);
}

//////////////////
// OpenGL stuff //
//////////////////
void RaySpotLight::drawOpenGL(int index){
	GLfloat light_color[]     = { color[0],     color[1],     color[2], 1.0 };
	GLfloat light_position[]  = { location[0],  location[1],  location[2], 1.0 };
	GLfloat light_direction[] = { -direction[0], -direction[1], -direction[2], 0.0 };

	glLightfv(GL_LIGHT0+index, GL_POSITION,       light_position);
	glLightfv(GL_LIGHT0+index, GL_SPOT_DIRECTION, light_direction);
	glLightf(GL_LIGHT0+index, GL_SPOT_CUTOFF,    180.0 * cutOffAngle/PI);
	glLightf(GL_LIGHT0+index, GL_SPOT_EXPONENT,  dropOffRate);
	glLightfv(GL_LIGHT0+index, GL_DIFFUSE,        light_color);
	glLightfv(GL_LIGHT0+index, GL_SPECULAR,       light_color);
	glLightf(GL_LIGHT0+index, GL_CONSTANT_ATTENUATION, constAtten);
	glLightf(GL_LIGHT0+index, GL_LINEAR_ATTENUATION, linearAtten);
	glLightf(GL_LIGHT0+index, GL_QUADRATIC_ATTENUATION, quadAtten);
	glEnable( GL_LIGHT0+index);
}
