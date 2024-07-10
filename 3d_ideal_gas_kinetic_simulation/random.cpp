#include <cmath>
#include <cstdlib>
#include "random.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace Random
{
double randomNorm(double mu, double sigma)
{
	//Box and Muller method
	double r1 = 0.;
	double r2 = 0.;
	while (r1 < 0.0000001) {
		r1 = double(rand()) / RAND_MAX; // uniform number between 0 and 1
		r2 = double(rand()) / RAND_MAX; // uniform number between 0 and 1
	}

	//mean 0 and width 1
	double x = std::sqrt(-2. * log(r1)) * cos(2. * M_PI * r2);

	x *= sigma; //scale to width = sigma
	x += mu; //shift to mean = mu
	return x;
}
};
