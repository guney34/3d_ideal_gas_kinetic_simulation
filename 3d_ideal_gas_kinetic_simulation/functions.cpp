#include "functions.h"

bool testFloat(double value, double test, double p)
{
	double diff = value - test;
	return std::abs(diff) < p;
}

bool test1()
{
	idg::vector testVector;
	if (testFloat(testVector.x, 0, 0.0001) && testFloat(testVector.y, 0, 0.0001) &&
		testFloat(testVector.z, 0, 0.0001)) {

		testVector.x = 10;
		testVector.y = 20;
		testVector.z = 30;

		return testFloat(testVector.x, 10, 0.0001) &&
			testFloat(testVector.y, 20, 0.0001) &&
			testFloat(testVector.z, 30, 0.0001);
	}
	else {
		return false;
	}
}

bool testModulus()
{
	idg::vector testVector(1, 2, 3);
	return testFloat(testVector.modSqr(), 14, 0.0001) &&
		testFloat(testVector.mod(), sqrt(14), 0.0001);
}

bool testDistance()
{
	idg::vector v1(1, 2, 3), v2(3, 2, 1);
	return testFloat(v1.distance(v2), sqrt(8), 0.0001);
}

bool testDot()
{
	idg::vector v1(1, 0, 1), v2(0, 1, 0);
	return testFloat(v1.dot(v2), 0, 0.0001);
}

bool testScale()
{
	idg::vector v(1, 1, 1);
	v.scale(3);
	return v.x == 3 && v.y == 3 && v.z == 3;
}

bool testUnit()
{
	idg::vector v1(3, 3, 3);
	idg::vector v2 = v1.unit();
	return testFloat(v2.mod(), 1, 0.0001) && testFloat(v1.dot(v2), v1.mod(), 0.0001);
}

bool testCross()
{
	idg::vector v1(1, 0, 0), v2(0, 1, 0), v3(0, 0, 1);
	idg::vector v4 = v1.cross(v2), v5 = v2.cross(v3), v6 = v3.cross(v1);
	return testFloat(v4.distance(v3), 0, 0.0001) &&
		testFloat(v5.distance(v1), 0, 0.0001) &&
		testFloat(v6.distance(v2), 0, 0.0001);
}

bool testOperators()
{
	idg::vector v1(1, 2, 3), v2(2, 4, 6);
	idg::vector v3 = v1 + v1;
	bool test1 = testFloat(v3.distance(v2), 0, 0.0001);

	idg::vector v4 = v2 - v1;
	bool test2 = testFloat(v4.distance(v1), 0, 0.0001);

	idg::vector v5 = -v1;
	idg::vector v6(-1, -2, -3);
	bool test3 = testFloat(v5.distance(v6), 0, 0.0001);

	return test1 && test2 && test3;
}

bool testParticle()
{
	idg::particle p;

	if (testFloat(p.pos.distance(idg::vector()), 0, 0.0001) &&
		testFloat(p.vel.distance(idg::vector()), 0, 0.0001))
	{
		p.pos = idg::vector(1, 2, 3);
		p.vel = idg::vector(4, 5, 6);

		return testFloat(p.pos.distance(idg::vector(1, 2, 3)), 0, 0.0001) &&
			testFloat(p.vel.distance(idg::vector(4, 5, 6)), 0, 0.0001);
	}
	else
	{
		return false;
	}
}

bool testMove() {
	idg::particle p(1, idg::vector(), idg::vector(1, 1, 1));
	p.move(1);

	return testFloat(p.pos.distance(idg::vector(1, 1, 1)), 0, 0.001);
}

bool testCollision()
{
	bool tests[5];
	//test time to collision calculation
	{
		idg::particle p1(1, idg::vector(), idg::vector(1));
		idg::particle p2(1, idg::vector(12), idg::vector(-1));
		tests[0] = testFloat(p1.timeToCollision(p2), 5, 0.0001);

		idg::particle p3(1, idg::vector(), idg::vector(1, 1));
		idg::particle p4(1, idg::vector(5, 5, 6.99999), idg::vector(0, 0, -1));
		tests[1] = testFloat(p3.timeToCollision(p4), 5, 0.0001);

		idg::particle p5(1, idg::vector(0, 3), idg::vector(1));
		idg::particle p6(1, idg::vector(12), idg::vector(-1, 0, 1));
		tests[2] = testFloat(p5.timeToCollision(p6), FLT_MAX, 0.0001);
	}
	//test velocities after collision
	{
		idg::particle p1(1, idg::vector(), idg::vector(1));
		idg::particle p2(1, idg::vector(5), idg::vector());
		p1.collideParticles(p2);
		tests[3] = testFloat(p1.vel.distance(idg::vector()), 0, 0.0001) &&
			testFloat(p2.vel.distance(idg::vector(1)), 0, 0.0001);

		idg::particle p3(1, idg::vector(), idg::vector(1));
		idg::particle p4(1, idg::vector(10), idg::vector(-0.5));
		p3.collideParticles(p4);
		tests[4] = testFloat(p3.vel.x, -0.5, 0.0001) &&
			testFloat(p4.vel.x, 1, 0.0001);
	}

	return tests[0] && tests[1] && tests[2] && tests[3] && tests[4];
}
