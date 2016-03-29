#include <stdlib.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include "rayGroup.h"

#include <algorithm>

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RayGroup::intersect(Ray3D ray, RayIntersectionInfo& iInfo, double mx)
{
	if (bBox.intersect(ray) < 0)
	{
		return -1;
	}

	Ray3D transformed_ray = getInverseMatrix().mult(ray);
	double s = transformed_ray.direction.length();
	transformed_ray.direction = transformed_ray.direction.unit();	
	double transformed_mx = s * mx;

	mx = -1;

	for (int i = 0; i < sNum; ++i)
	{
		double dist = shapes[i]->bBox.intersect(transformed_ray);
		if (dist < 0)
		{
			dist = std::numeric_limits<double>::max();
		}
		hits[i].t = dist;
		hits[i].shape = shapes[i];
	}

	qsort(hits, sNum, sizeof(RayShapeHit), RayShapeHit::Compare);

	for (int i = 0; i < sNum; ++i)
	{
		double dist = hits[i].shape->intersect(transformed_ray, iInfo, transformed_mx);
		if (dist > 0)
		{
			transformed_mx = dist;
			mx = transformed_mx / s;
			iInfo.iCoordinate = getMatrix().multPosition(iInfo.iCoordinate);
			iInfo.normal = getNormalMatrix().multDirection(iInfo.normal);
			iInfo.normal = iInfo.normal.unit();
			break;
		}
	}

	return mx;
}

BoundingBox3D RayGroup::setBoundingBox(void)
{
	bBox = BoundingBox3D();
	for (int i = 0; i < sNum; ++i)
	{
		shapes[i]->setBoundingBox();
		bBox += shapes[i]->bBox;
	}

	bBox = bBox.transform(getMatrix());

	return bBox;
}

int StaticRayGroup::set(void)
{
	inverseTransform = localTransform.invert();
	normalTransform = localTransform.transpose().invert();
	return 1;
}
//////////////////
// OpenGL stuff //
//////////////////
int RayGroup::getOpenGLCallList(void){
	return 0;
}

int RayGroup::drawOpenGL(int materialIndex){
	return -1;
}

/////////////////////
// Animation Stuff //
/////////////////////
Matrix4D ParametrizedEulerAnglesAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedClosestRotationAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedRotationLogarithmAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedQuaternionAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
