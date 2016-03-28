#include <math.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include "rayPointLight.h"
#include "rayScene.h"
#include <algorithm>

////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RayPointLight::getDiffuse(Point3D cameraPosition,RayIntersectionInfo& iInfo)
{
	Point3D L = location - iInfo.iCoordinate;
	double d = L.length(); L = L / d;
	double cos_theta = std::max(0.0, iInfo.normal.dot(L));
	Point3D IL = color / (constAtten + linearAtten * d + quadAtten * d * d);
	Point3D Kd = iInfo.material->diffuse;
	return Kd.mult(IL * cos_theta);
}

Point3D RayPointLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	return Point3D();
}
int RayPointLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
	return 0;
}
Point3D RayPointLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){
	return Point3D(1,1,1);
}


//////////////////
// OpenGL stuff //
//////////////////
void RayPointLight::drawOpenGL(int index){
}
