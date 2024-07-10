#include "vector.h"
#include <cmath>
namespace idg
{
double vector::modSqr() const
{
	return x*x + y*y + z*z;
}
double vector::mod() const
{
	return sqrt(modSqr());
}
double vector::dot(const vector& a) const
{
	return x*a.x + y*a.y + z*a.z;
}
double vector::distance(const vector& a) const
{
	vector diff(x - a.x, y - a.y, z - a.z);
	return diff.mod();
}
void vector::scale(double f)
{
	x *= f;
	y *= f;
	z *= f;
}
vector vector::unit() const
{
	vector v(x, y, z);
	v.scale(1 / v.mod());
	return v;
}
vector vector::cross(const vector& a) const
{
	return vector(y*a.z - z*a.y, z*a.x - x*a.z, x*a.y - y*a.x);
}

//constructors
vector& vector::operator+=(const vector& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

vector vector::operator+(const vector& v) const
{
	vector v2(*this);
	return v2 += v;
}

vector& vector::operator-=(const vector& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

vector vector::operator-(const vector& v) const
{
	vector v2(*this);
	return v2 -= v;
}

vector vector::operator-() const
{
	vector v2(*this);
	v2.scale(-1);
	return v2;
}
}