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
}
