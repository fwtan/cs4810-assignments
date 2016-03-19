#include <stdlib.h>
#include <math.h>

#include <SVD/SVDFit.h>
#include <SVD/MatrixMNTC.h>

#include "geometry.h"


#include <limits>
#include <algorithm>
using namespace std;


///////////////////////
// Ray-tracing stuff //
///////////////////////
double BoundingBox3D::intersect(const Ray3D& ray) const 
{
	double min_d = std::numeric_limits<double>::max();

	Point3D p0 = ray.position;
	Point3D v = ray.direction;

	if (p0[0] < 0)
	{
		Point3D p1 = p[1];
		min_d = min(min_d, (p1[0] - p0[0])/v[0]);
	}
	else
	{
		Point3D p1 = p[0];
		min_d = min(min_d, (p1[0] - p0[0])/v[0]);
	}

	if (p0[1] < 0)
	{
		Point3D p1 = p[1];
		min_d = min(min_d, (p1[1] - p0[1])/v[1]);
	}
	else
	{
		Point3D p1 = p[0];
		min_d = min(min_d, (p1[1] - p0[1])/v[1]);
	}

	if (p0[2] < 0)
	{
		Point3D p1 = p[1];
		min_d = min(min_d, (p1[2] - p0[2])/v[2]);
	}
	else
	{
		Point3D p1 = p[0];
		min_d = min(min_d, (p1[2] - p0[2])/v[2]);
	}

	return min_d;
}

/////////////////////
// Animation stuff //
/////////////////////
Matrix3D::Matrix3D(const Point3D& e){
	(*this)=Matrix3D();
}

Matrix3D::Matrix3D(const Quaternion& q){
	(*this)=Matrix3D();
}
Matrix3D Matrix3D::closestRotation(void) const {
	return (*this);
}
/* While these Exp and Log implementations are the direct implementations of the Taylor series, the Log
 * function tends to run into convergence issues so we use the other ones:*/
Matrix3D Matrix3D::Exp(const Matrix3D& m,int iter){
	return m;
}
