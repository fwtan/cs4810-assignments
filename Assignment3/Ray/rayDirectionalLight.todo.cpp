#include <math.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include "rayDirectionalLight.h"
#include "rayScene.h"
#include <algorithm>

////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RayDirectionalLight::getDiffuse(Point3D cameraPosition, RayIntersectionInfo& iInfo)
{
	Point3D L = - direction.unit();
	Point3D N = iInfo.normal.unit();
	double cos_theta = N.dot(L);
	if (cos_theta <= 0)
	{
		return Point3D();
	}
	Point3D Kd = iInfo.material->diffuse;
	return Kd.mult(color * cos_theta);
}

Point3D RayDirectionalLight::getSpecular(Point3D cameraPosition, RayIntersectionInfo& iInfo)
{
	Point3D L = - direction.unit();
	Point3D N = iInfo.normal.unit();
	double cos_theta = N.dot(L);
	if (cos_theta <= 0)
	{
		return Point3D();
	}

	Point3D V = (cameraPosition - iInfo.iCoordinate).unit();
	Point3D R = (- L + N * 2 * cos_theta).unit();
	Point3D Ks = iInfo.material->specular;
	double cos_beta = V.dot(R);
	if (cos_beta <= 0)
	{
		return Point3D();
	}
	return Ks.mult(color * pow(cos_beta, iInfo.material->specularFallOff));
}

int RayDirectionalLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount)
{
	double factor = 0.001;
	
	BoundingBox3D bbox = shape->bBox;
	Point3D p0 = bbox.p[0];
	Point3D p1 = bbox.p[1];

	double dist = (p1 - p0).length();

	Ray3D ray;
	ray.position  = iInfo.iCoordinate + iInfo.normal * (dist * factor);
	ray.direction = - direction / direction.length();

	RayIntersectionInfo iNewInfo;
	if (shape->intersect(ray, iNewInfo) > 0)
	{
		++isectCount;
		return 1;
	}

	return 0;
}

Point3D RayDirectionalLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit)
{
	double factor = 0.001;
	
	BoundingBox3D bbox = shape->bBox;
	Point3D p0 = bbox.p[0];
	Point3D p1 = bbox.p[1];

	double dist = (p1 - p0).length();

	Ray3D ray;
	ray.position  = iInfo.iCoordinate + iInfo.normal * (dist * factor);
	ray.direction = - direction / direction.length();

	RayIntersectionInfo iNewInfo;
	Point3D trans(1,1,1);
	if (shape->intersect(ray, iNewInfo) > 0)
	{
		Point3D intersected_trans = iNewInfo.material->transparent;
		Point3D factor = intersected_trans.mult(intersected_trans);
		if (factor[0] < cLimit[0] && factor[1] < cLimit[1] && factor[2] < cLimit[2])
		{
			return Point3D();
		}

		trans = factor.mult(transparency(iNewInfo, shape, cLimit));
	}
	
	return trans;
}

//////////////////
// OpenGL stuff //
//////////////////
void RayDirectionalLight::drawOpenGL(int index)
{
	GLfloat light_color[] = { color[0], color[1], color[2], 1.0 };
	GLfloat light_direction[] = { -direction[0], -direction[1], -direction[2], 0.0 };

	glLightfv(GL_LIGHT0+index, GL_POSITION, light_direction);
	glLightfv(GL_LIGHT0+index, GL_DIFFUSE,  light_color);
	glLightfv(GL_LIGHT0+index, GL_SPECULAR, light_color);
	glEnable( GL_LIGHT0+index);
}
