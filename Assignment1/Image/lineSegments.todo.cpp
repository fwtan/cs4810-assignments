#include "lineSegments.h"
#include <math.h>

float OrientedLineSegment::length(void) const
{
	return sqrt(static_cast<float>((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float OrientedLineSegment::distance(const int& x,const int& y) const
{
	float vx1;
	float vy1;
	getPerpendicular(vx1, vy1);

	float vx2 = x - x1;
	float vy2 = y - y1;

	return vx1 * vx2 + vy1 * vy2;
}

void  OrientedLineSegment::getPerpendicular(float& x,float &y) const
{
	float vx1 = x2 - x1;
	float vy1 = y2 - y1;

	float len1 = sqrt(vx1 * vx1 + vy1 * vy1);

	x = vy1/len1;
	y = -vx1/len1;
}

void  OrientedLineSegment::GetSourcePosition(const OrientedLineSegment& source,const OrientedLineSegment& destination,
											 const int& targetX,const int& targetY,
											 float& sourceX,float& sourceY)
{

	float vx1, vy1, vx2, vy2;
	vx1 = targetX 		 - destination.x1;
	vy1 = targetY 		 - destination.y1;
	vx2 = destination.x2 - destination.x1;
	vy2 = destination.y2 - destination.y1;

	float u = (vx1 * vx2 + vy1 * vy2)/(vx2 * vx2 + vy2 * vy2);
	float v = destination.distance(targetX, targetY);

	source.getPerpendicular(vx1, vy1);

	vx2 = source.x2 - source.x1;
	vy2 = source.y2 - source.y1;

	sourceX=sourceY=0;
}
