#include <iostream>
#include "Physics.h"
#include "Random.h"

float mass[MAXN];
float radius[MAXN];
glm::vec3 positions[MAXN];
glm::vec3 velocity[MAXN];

int ic = -1;
int jc = -1;
float tc = 0;
float tf = dtf;

/*
* TODO:
* 1. Make Names More Understandable:
* - uniform. <- Maybe make wrapper with random in name. 
				ie. randomUniform
* 2. Generate Balls in the second loop: Initialize Func
* - Generate ball i then check for interference
* - Would have to pre-generate ball 0 before the loop
* 3. 
*/
void DeclareBalls()
{
	for (int i = 0; i < MAXN; ++i)
	{
		positions[i] = glm::vec3(0.0f, 0.0f, 0.0f);
		velocity[i] = glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

void Initialize()
{
	for (unsigned int i = 0; i < n; ++i)
	{
		radius[i] = radiusMin + (uniform() * (radiusMax - radiusMin));
		mass[i] = (radius[i] * radius[i] * radius[i]) / 3000.0f;
		positions[i] = UniformPosition() * (rc - radius[i]);
		velocity[i] = UniformDirection() * speed;
	}
	/*
	* Check if balls were generated clipping into each other.
	* If so then regenerate ball posisition for 
	*/
	for (unsigned int i = 1; i < n; ++i)
	{
		bool interfere = true;
		while (interfere)
			for (unsigned int j = 0; j < i; ++j)
				if (interfere = Interfere(i, j)) {
					positions[i] = UniformPosition() * (rc - radius[i]);
					break;
				}
	}
}

void AdvanceToNextFrame()
{
	while (tc < tf)
	{
		Jump(tc);
		HandleCollisions();
		tf -= tc;
		tc = Predict();
	}
	Jump(tf);
	tc = Predict();
}

bool Interfere(unsigned int i, unsigned int j)
{
	glm::vec3 distance = positions[j] - positions[i];
	return glm::dot(distance, distance) < (radius[i]+radius[j])*(radius[i]+radius[j]);
}

void Jump(float t)
{
	for (unsigned int i = 0; i < n; ++i)
	{
		positions[i] += (velocity[i] * t);
	}
}

float Predict()
{
	float leastTime = 100000.0f;
	float tmpLeastTime = 0.0f;
	ic = jc = -1;


	for (unsigned int i = 0; i < n; ++i)
	{
		tmpLeastTime = TimeToBounce(i);
		if (leastTime > tmpLeastTime && tmpLeastTime >= 0)
		{
			leastTime = tmpLeastTime;
			ic = i;
		}
	}
	for (unsigned int i = 1; i < n; ++i)
	{
		for (unsigned int j = 0; j < i; ++j)
		{
			tmpLeastTime = TimeToCollision(i, j);
			if (leastTime > tmpLeastTime && tmpLeastTime >= 0)
			{
				leastTime = tmpLeastTime;
				ic = i;
				jc = j;
			}
		}
	}
	return leastTime;
}

float TimeToBounce(unsigned int i)
{
	glm::vec3 CP = positions[i] - container;

	float a = glm::dot(velocity[i], velocity[i]);
	float b = 2 * glm::dot(CP, velocity[i]);
	float c = glm::dot(CP, CP) - ((rc - radius[i]) * (rc - radius[i]));

	float tb = -b + sqrt((b * b) - (4 * a * c));
	tb /= (2 * a);
	return (tb >= 0.0f) ? tb : -1;
}

float TimeToCollision(unsigned int i, unsigned int j)
{
	glm::vec3 IJ = positions[j] - positions[i];
	glm::vec3 DV = velocity[j] - velocity[i];
	
	float a = glm::dot(DV, DV);
	float b = 2 * glm::dot(IJ, DV);
	float c = glm::dot(IJ, IJ) - ((radius[i] + radius[j]) * (radius[i] + radius[j]));

	float descriminant = sqrt((b * b) - (4 * a * c));
	if (descriminant < 0) return -1;
	float tc = (-b - descriminant) / (2 * a);
	return (tc >= 0.0f) ? tc : -1;
}

void HandleCollisions()
{
	if (jc == -1) {
		ComputeVelocityAfterBounce(ic);
		ic = -1;
	}
	else
	{
		ComputeVelocityAfterCollision(ic, jc);
		ic = jc = -1;
	}
}

void ComputeVelocityAfterBounce(unsigned int i)
{
	glm::vec3 CP = positions[i] - container;
	velocity[i] += (-2 * glm::dot(CP, velocity[i]) / glm::dot(CP, CP)) * CP;
}

void ComputeVelocityAfterCollision(unsigned int i, unsigned int j)
{
	glm::vec3 X = glm::normalize(positions[j] - positions[i]);
	glm::vec3 DV = velocity[i] - velocity[j];

	float massFactor1 = (2 * mass[j]) / (mass[i] + mass[j]);
	float massFactor2 = (2 * mass[i]) / (mass[i] + mass[j]);

	velocity[i] -= massFactor1 * (glm::dot(X, DV) * X);
	velocity[j] += massFactor2 * (glm::dot(X, DV) * X);
}

void LogPositions()
{
	for (unsigned int i = 0; i < n; ++i)
	{
		std::cout << "positions[" << i << "].x: " << positions[i].x << std::endl;
		std::cout << "positions[" << i << "].y: " << positions[i].y << std::endl;
		std::cout << "positions[" << i << "].z: " << positions[i].z << std::endl;
		std::cout << std::endl;
	}
}

void LogRadii()
{
	for (unsigned int i = 0; i < n; ++i)
	{
		std::cout << "radius[" << i << "].x: " << radius[i] << std::endl;
		std::cout << std::endl;
	}
}