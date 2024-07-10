#pragma once
#include "particle.h"
#include <vector>

namespace idg
{
struct box
{
	std::vector<particle> particles;
	double size;

	box(double size = 500) : size(size) { }

	void addParticle(const particle& p);

	double timeToWallCollision(int wall, const particle& p) const;
	void doWallCollision(int wall, particle& p);

	//find soonest collison and move all particles
	double Step();

	std::vector<int> nParticlesOctant() const; //num particles in every octant
};
}

