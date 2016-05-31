#include <math.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include "rayScene.h"
#include "raySphere.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RaySphere::intersect(Ray3D ray, RayIntersectionInfo& iInfo, double mx)
{
	Point3D V = ray.direction.unit();
	Point3D P = ray.position;
	Point3D L = center - P;
	
	double tca = L.dot(V);
	double d2 = L.dot(L) - tca * tca;
	double r2 = radius * radius;
	
	if (d2 >= r2)
	{
		return -1;
	}

	double thc = sqrt(r2 - d2);

	double t = tca - thc;

	if (t <= 0)
	{
		return -1;
	}

	if (mx > 0 && t > mx)
	{
		return -1;
	}

	iInfo.iCoordinate = P + V * t;
	iInfo.normal = (iInfo.iCoordinate - center).unit();
	iInfo.material = material;

	return t;
}

BoundingBox3D RaySphere::setBoundingBox(void)
{
	double diag_len = sqrt(3) * radius;
	Point3D offset = Point3D(diag_len, diag_len, diag_len);
	bBox = BoundingBox3D(center - offset, center + offset);
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RaySphere::drawOpenGL(int materialIndex){

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
	gluSphere(quadric, radius, 100, 100);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	delete quadric;

	return used_mt;
}
