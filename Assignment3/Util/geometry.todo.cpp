#include <stdlib.h>
#include <math.h>

#include <SVD/SVDFit.h>
#include <SVD/MatrixMNTC.h>

#include "geometry.h"


#include <limits>
#include <algorithm>
using namespace std;


bool bContain2D(Point2D p1, Point2D p2, Point2D query)
{
    return (query[0] >= p1[0] && query[0] <= p2[0] &&
            query[1] >= p1[1] && query[1] <= p2[1]);
}

bool bContain3D(Point3D p1, Point3D p2, Point3D query)
{
    return (query[0] >= p1[0] && query[0] <= p2[0] &&
            query[1] >= p1[1] && query[1] <= p2[1] && 
            query[2] >= p1[2] && query[2] <= p2[2]);
}

///////////////////////
// Ray-tracing stuff //
///////////////////////
double BoundingBox3D::intersect(const Ray3D& ray) const 
{
    Point3D ray_c = ray.position;
    Point3D ray_v = ray.direction.unit();
    Point3D p1 = p[0];
    Point3D p2 = p[1];


    // check if the start point of the ray is in the box
    if (bContain3D(p1, p2, ray_c))
    {
        return 0;
    }

    double t;
    Point3D isectP;
    double min_d = std::numeric_limits<double>::max();

    t = (p2[0] - ray_c[0]) / ray_v[0];
    isectP = ray_c + ray_v * t;
    if (bContain2D(Point2D(p1[1], p1[2]), Point2D(p2[1], p2[2]), Point2D(isectP[1], isectP[2])))
    {
        min_d = min(min_d, t);
    }

    t = (p1[0] - ray_c[0]) / ray_v[0];
    isectP = ray_c + ray_v * t;
    if (bContain2D(Point2D(p1[1], p1[2]), Point2D(p2[1], p2[2]), Point2D(isectP[1], isectP[2])))
    {
        min_d = min(min_d, t);
    }

    t = (p2[1] - ray_c[1]) / ray_v[1];
    isectP = ray_c + ray_v * t;
    if (bContain2D(Point2D(p1[0], p1[2]), Point2D(p2[0], p2[2]), Point2D(isectP[0], isectP[2])))
    {
        min_d = min(min_d, t);
    }

    t = (p1[1] - ray_c[1]) / ray_v[1];
    isectP = ray_c + ray_v * t;
    if (bContain2D(Point2D(p1[0], p1[2]), Point2D(p2[0], p2[2]), Point2D(isectP[0], isectP[2])))
    {
        min_d = min(min_d, t);
    }

    t = (p2[2] - ray_c[2]) / ray_v[2];
    isectP = ray_c + ray_v * t;
    if (bContain2D(Point2D(p1[0], p1[1]), Point2D(p2[0], p2[1]), Point2D(isectP[0], isectP[1])))
    {
        min_d = min(min_d, t);
    }

    t = (p1[2] - ray_c[2]) / ray_v[2];
    isectP = ray_c + ray_v * t;
    if (bContain2D(Point2D(p1[0], p1[1]), Point2D(p2[0], p2[1]), Point2D(isectP[0], isectP[1])))
    {
        min_d = min(min_d, t);
    }

    if (min_d == std::numeric_limits<double>::max())
    {
        min_d = -1;
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
