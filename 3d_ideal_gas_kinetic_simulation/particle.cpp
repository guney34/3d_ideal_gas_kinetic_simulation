#include "particle.h"
#include <cmath>

namespace idg
{
//Moves particle by vt
void particle::move(double t)
{
	vector delta(vel);
	delta.scale(t);
	pos += delta;
}

double particle::timeToCollision(const particle& particle) const
{
	vector r0 = particle.pos - pos;
	vector v = particle.vel - vel;

	//If the vel is too small, the time to next collision is set to the largest possible double
	if (v.mod() < 0.000001)
	{
		return FLT_MAX;
	}

	double tca = -r0.dot(v) / v.modSqr();
	if (tca < 0)
	{
		return FLT_MAX;
	}

	vector s(v);
	s.scale(tca);

	if ((r0.modSqr() - s.modSqr()) > 4 * rad*rad)
	{
		return FLT_MAX;
	}

	double d = sqrt(4 * rad*rad - (r0.modSqr() - s.modSqr()));
	double tcol = tca - d / v.mod();

	if (tcol > 0)
	{
		return tcol;
	}
	else
	{
		return FLT_MAX;
	}
}

void particle::collideParticles(particle& particle)
{
	double tca = timeToCollision(particle);

	if (tca < 0 || std::abs(tca - FLT_MAX) < 0.0001)
	{
		return;
	}

	move(tca); //move particles to collision point
	particle.move(tca);

	vector n = (particle.pos - pos).unit();
	vector v1(n), v2(n);

	v1.scale(vel.dot(n)); //calculate the change in vel due to collision
	v2.scale(particle.vel.dot(n));
	vector deltaV = v2 - v1;

	vel += deltaV; //set vels of particles post collision
	particle.vel -= deltaV;
}
}