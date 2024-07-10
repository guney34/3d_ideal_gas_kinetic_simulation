#include "functions.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "random.h"

int main()
{
	int seed = 103; //pseudorandom number generator seed
	int numParticles = 1000;
	int numCollisions = 1000;
	int numDataPoints = 50;
	int boxSize = 500; //relative to particle radius = 1
	
	//unit testing
	if (test1()) std::cout << "Test 1 SUCCESS" << std::endl;
	else std::cout << "Test 1 FAILED" << std::endl;
	if (testModulus()) std::cout << "Test Modulus : SUCCESS" << std::endl;
	else std::cout << "Test Modulus : FAILED" << std::endl;
	if (testDistance()) std::cout << "Test Distance : SUCCESS" << std::endl;
	else std::cout << "Test Distance : FAILED" << std::endl;
	if (testDot()) std::cout << "Test Dot : SUCCESS" << std::endl;
	else std::cout << "Test Dot : FAILED" << std::endl;
	if (testScale()) std::cout << "Test Scale : SUCCESS" << std::endl;
	else std::cout << "Test Scale : FAILED" << std::endl;
	if (testUnit()) std::cout << "Test Unit : SUCCESS" << std::endl;
	else std::cout << "Test Unit : FAILED" << std::endl;
	if (testCross()) std::cout << "Test Cross : SUCCESS" << std::endl;
	else std::cout << "Test Cross : FAILED" << std::endl;
	if (testOperators()) std::cout << "Test Operators : SUCCESS" << std::endl;
	else std::cout << "Test Operators : FAILED" << std::endl;
	if (testParticle()) std::cout << "Test Particle : SUCCESS" << std::endl;
	else std::cout << "Test Particle : FAILED" << std::endl;
	if (testMove()) std::cout << "Test Move : SUCCESS" << std::endl;
	else std::cout << "Test Move : FAILED" << std::endl;
	if (testCollision()) std::cout << "Test Collision : SUCCESS" << std::endl;
	else std::cout << "Test Collision : FAILED" << std::endl;

	idg::box box(boxSize);
	double time = 0;
	std::srand(seed);

	for (int i = 0; i < numParticles; i++) //adds particles to box
	{
		//pos components have a pseudo-random uniform distribution in Octant: +++
		double x = 249 * double(std::rand()) / RAND_MAX;
		double y = 249 * double(std::rand()) / RAND_MAX;
		double z = 249 * double(std::rand()) / RAND_MAX;

		idg::vector p(x, y, z);

		//vel components have a pseudo-random normal distribution
		idg::vector v(Random::randomNorm(0, 10),
			Random::randomNorm(0, 10),
			Random::randomNorm(0, 10));

		idg::particle particle(1, p, v);
		box.addParticle(particle);
	}

	std::ofstream f("data.csv"); //data, csv format

	f << "collisions,time,O(---),O(--+),O(-+-),O(-++),O(+--),O(+-+),O(++-),O(+++)" << std::endl;
	f << 0 << "," << time << "," <<
		box.nParticlesOctant()[0] << "," <<
		box.nParticlesOctant()[1] << "," <<
		box.nParticlesOctant()[2] << "," <<
		box.nParticlesOctant()[3] << "," <<
		box.nParticlesOctant()[4] << "," <<
		box.nParticlesOctant()[5] << "," <<
		box.nParticlesOctant()[6] << "," <<
		box.nParticlesOctant()[7] << std::endl;

	for (int i = 0; i < numCollisions; i++)	//perform collisions
	{
		time += box.Step(); //find next collision and move all particles

		if ((i + 1) % (numCollisions/numDataPoints) == 0) //how often to write data
		{
			f << i + 1 << "," << time << "," <<
				box.nParticlesOctant()[0] << "," <<
				box.nParticlesOctant()[1] << "," <<
				box.nParticlesOctant()[2] << "," <<
				box.nParticlesOctant()[3] << "," <<
				box.nParticlesOctant()[4] << "," <<
				box.nParticlesOctant()[5] << "," <<
				box.nParticlesOctant()[6] << "," <<
				box.nParticlesOctant()[7] << std::endl;
		}
	}
	f.close();
	int x;
	std::cin >> x;
}