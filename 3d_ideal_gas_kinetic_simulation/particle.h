#pragma once
#include "vector.h"
#include <cfloat>

namespace idg
{
struct particle
{
	vector pos, vel;
	double rad;

	particle(double r = 1, const vector& p = vector(),
		const vector& a = vector())
		: rad(r), pos(p), vel(a) {}

	void move(double t); //moves particle by vt

	//time to collision with a chosen particle
	double timeToCollision(const particle& particle) const;

	//move particles to collision and update velocities
	void collideParticles(particle& particle);
};
}
