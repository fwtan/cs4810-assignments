#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rayTriangle.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
void RayTriangle::initialize(void)
{
	v1 = v[1]->position - v[0]->position;
	v2 = v[2]->position - v[0]->position;

	plane.normal = (v1.crossProduct(v2)).unit();
	plane.distance = - v[0]->position.dot(plane.normal);
}

double RayTriangle::intersect(Ray3D ray, RayIntersectionInfo& iInfo, double mx)
{
	Point3D V = ray.direction.unit();
	Point3D P = ray.position;
	Point3D N = plane.normal;

	for (int i = 0; i < 3; ++i)
	{
		Point3D tmpV1 = v[i]->position - P;
		Point3D tmpV2 = v[(i + 1) % 3]->position - P;
		Point3D tmpN = tmpV2.crossProduct(tmpV1);
		if (V.dot(tmpN) <= 0)
		{
			return -1;
		}
	}

	double t = - plane.evaluate(P) / V.dot(N);

	if (t <= 0)
	{
		return -1;
	}

	if (mx > 0 && t > mx)
	{
		return -1;
	}

	iInfo.iCoordinate = P + V * t;
	iInfo.normal = plane.normal;
	iInfo.material = material;

	return t;
}

BoundingBox3D RayTriangle::setBoundingBox(void)
{
	Point3D pts[3];
	for (int i = 0; i < 3; ++i)
	{
		pts[i] = v[i]->position;
	}
	bBox = BoundingBox3D(pts, 3);
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RayTriangle::drawOpenGL(int materialIndex){
	return -1;
}
