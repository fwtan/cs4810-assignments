#include "rayScene.h"
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include <math.h>


///////////////////////
// Ray-tracing stuff //
///////////////////////

Point3D RayScene::Reflect(Point3D v,Point3D n){

	return v - n * 2 * (v.dot(n));
}

int RayScene::Refract(Point3D v,Point3D n,double ir,Point3D& refract){
	return 0;
}

Ray3D RayScene::GetRay(RayCamera* camera,int i,int j,int width,int height){

	double d = 1.0; 

	//Point3D c = camera->position + camera->direction * d;

	double h = d * tan(camera->heightAngle);
	double w = h * camera->aspectRatio;

	// Point3D t = c - up;
	// Point3D b = c + up;
	// Point3D l = c - right;
	// Point3D r = c + right;

	// double u = l + (r - l) * ((i + 0.5)/width);
	// double v = b + (t - b) * ((j + 0.5)/height);

	double u = -w + 2 * w * ((i + 0.5)/width);
	double v = -h + 2 * h * ((j + 0.5)/height);

	return Ray3D(camera->position, camera->direction * (-d) + camera->right * u + camera->up * v);
}

Point3D RayScene::GetColor(Ray3D ray,int rDepth,Point3D cLimit){
	return Point3D();
}

//////////////////
// OpenGL stuff //
//////////////////
void RayMaterial::drawOpenGL(void){
}
void RayTexture::setUpOpenGL(void){
}
