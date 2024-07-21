#include "box.h"

namespace idg
{
double box::timeToWallCollision(unsigned int wall, const particle& p) const
{
	double twc;
	double x = 0, v = 0;

	//Obtain the required components for vel and pos
	switch (wall)
	{
	case 1:
		x = p.pos.x;
		v = p.vel.x;
		break;
	case 2:
		x = p.pos.y;
		v = p.vel.y;
		break;
	case 3:
		x = p.pos.z;
		v = p.vel.z;
		break;
	}

	//Calculate time to collision based on the value of the vel component
	if (v > 0) {
		twc = ((size / 2) - x) / v;
	}
	else if (v < 0) {
		twc = (-(size / 2) - x) / v;
	}
	else {
		twc = FLT_MAX;
	}
	return twc;
}

void box::doWallCollision(unsigned int wall, particle& p)
{
	//Move the particle to the collision point
	p.move(timeToWallCollision(wall, p));

	double x = p.vel.x;
	double y = p.vel.y;
	double z = p.vel.z;

	//Invert the direction of the vel based on the wall the particle collided with
	switch (wall) {
	case 1:
		p.vel = vector(-x, y, z);
		break;
	case 2:
		p.vel = vector(x, -y, z);
		break;
	case 3:
		p.vel = vector(x, y, -z);
		break;
	}
}

double box::Step()
{
	double timeToNextCollision = FLT_MAX;
	unsigned int collisionType = 0;
	int collider1 = -1, collider2 = -1;

	//Loop over all particles
	for (unsigned int i = 0; i < particles.size(); ++i) {

		double t1 = timeToWallCollision(1, particles[i]);
		double t2 = timeToWallCollision(2, particles[i]);
		double t3 = timeToWallCollision(3, particles[i]);
		double tW;   //Shortest time for a wall collision
		unsigned int wall;

		//Find the shortest time to a wall collision
		if (t1 < t2 && t1 < t3)
		{
			tW = t1;
			wall = 1;
		}
		else if (t2 < t3 && t2 < t1)
		{
			tW = t2;
			wall = 2;
		}
		else
		{
			tW = t3;
			wall = 3;
		}

		//Check if time to wall collision is smaller than the current time to the closest collision
		if (tW < timeToNextCollision)
		{
			timeToNextCollision = tW;
			collider1 = (signed int)i;
			collisionType = wall;
		}

		//Starts at i+1 so every particle is compared to every other particle only once
		for (unsigned int j = i + 1; j < particles.size(); ++j)
		{
			//Shortest time for particle collision
			double tP = particles[i].timeToCollision(particles[j]);

			//Check if time to particle collision is smaller than the current time to the closest collision
			if (tP < timeToNextCollision)
			{
				timeToNextCollision = tP;
				collisionType = 0;
				collider1 = (signed int)i;
				collider2 = (signed int)j;
			}
		}
	}

	//Collide collider particles
	if ((collisionType == 0) && (collider1 >= 0) && (collider2 >= 0))
	{
		particles[(unsigned int)collider1].collideParticles(particles[(unsigned int)collider2]);
	}
	else
	{
		doWallCollision(collisionType, particles[collider1]);
	}

	//Move all non-collider particles by vt
	for (unsigned int k = 0; k < particles.size(); k++)
	{
		if ((signed int)k != collider1 && (signed int)k != collider2)
		{
			particles[k].move(timeToNextCollision);
		}
	}
	return timeToNextCollision;
}

//Simple function to return a std::vector that stores the number of particles in each octant
std::vector<int> box::nParticlesOctant() const
{
	std::vector<int> particlesOctant = { 0,0,0,0,0,0,0,0 };

	for (unsigned i = 0; i < particles.size(); ++i)
	{
		++particlesOctant[(((int)(particles[i].pos.x) >= 0) << 2) //x>=0 represented as 100
			+ (((int)(particles[i].pos.y) >= 0) << 1) //y>=0 represented as 010
			+ ((int)(particles[i].pos.z) >= 0)];      //z>=0 represented as 001
	}
	return particlesOctant;
}
}