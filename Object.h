#include "ArthurLib/Arthur.cpp"

struct Object
{
	vector v;
	
	double x,y;
	double m;

	Object() : m(0), x(0), y(0) {} 
	Object(double _x, double _y, double _m, double xv, double yv) : x(_x), y(_y), m(_m), v(xv,yv) {}

};
