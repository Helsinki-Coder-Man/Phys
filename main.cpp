#include <iostream>
#include <cmath>
#include <unistd.h>

#include "Object.h"

#define G pow(6.67 * 10,-11)
#define PI 3.14159265358979323

void setLength(vector& v, double length);
double getLength(vector v);

void setAngle(vector& v, double a){
	double length = getLength(v);

	v.direction = cos(a) * length;
	v.magnitude = sin(a) * length;

}

double getAngle(vector v){
	return atan2(v.magnitude , v.direction); 
}

void setLength(vector& v, double length){
	double angle = getAngle(v);

	v.direction = cos(angle) * length;
	v.magnitude = sin(angle) * length;
}

double getLength(vector v){
	return sqrt(v.direction * v.direction + v.magnitude * v.magnitude);
}

double angle(Object o, Object o1){
	return atan2(o1.y - o.y, o1.x - o.x);
}

double distance(Object o, Object o1){
	double dx = o1.x - o.x;
	double dy = o1.y - o.y;
	
	return sqrt(dx*dx + dy*dy);
}

double gravitation(double m1, double m2, double r){
	return (m1*m2) / (r*r);
}

double gravitate(Object& o, Object o1)
{
	vector g;
	double d = distance(o,o1);
	double a = angle(o, o1);

	double gr  = gravitation(o.m, o1.m, d);
	setLength(g, gr);	
	setAngle(g, a);

	o.v = o.v + g;
	std::cout << g.direction << 'D' << g.magnitude << '\t' << "x: " << o.v.direction << " y:" << o.v.magnitude;
	
}

void print(Object o, Object o1, double r)
{
	std::cout << "\nEarth coordinates: " << '(' << o.x << ',' << o.y << ')' << " | " << "Sun coordinates: " << '(' << o1.x << ',' << o1.y << ')';
}

int main()
{
	Object Earth (100,100,1,10,-PI/2);
	Object Sun (0,0,20000,0,0);

	while(1)
	{
	 double r = Sun.x - Earth.x / Sun.y - Earth.y;
	 
	 gravitate(Earth,Sun);
	 
	 Earth.x += Earth.v.direction;
	 Earth.y += Earth.v.magnitude;

	 print(Earth,Sun,r);
	 sleep(0.25);
	 
	}

	
	
	

}
