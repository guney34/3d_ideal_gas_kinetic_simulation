#pragma once
namespace idg
{
struct vector
{
	double x, y, z;

	vector(double a = 0, double b = 0, double c = 0) : x(a), y(b), z(c) { }

	vector& operator+=(const vector& v);
	vector operator+(const vector& v) const;
	vector& operator-=(const vector& v);
	vector operator-(const vector& v) const;
	vector operator-() const;

	double modSqr() const;
	double mod() const;
	double dot(const vector& a) const;
	double distance(const vector& a) const;

	void scale(double f);
	vector unit() const;
	vector cross(const vector& a) const;
};
}

