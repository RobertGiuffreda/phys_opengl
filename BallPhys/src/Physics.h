#pragma once
#include <glm.hpp>
#define MAXN 1024

/* Constants */
const unsigned int n = 30;
const float radiusMin = 10.0f;
const float radiusMax = 40.0f;
const float radiusToColor = (255.0f / (radiusMax - radiusMin));
const float speed = 50.0f;
const glm::vec3 container = glm::vec3(0.0f, 0.0f, 0.0f);
const float rc = 300.0f;
const float dtf = (1.0f / 60.0f);		// Time between frames. (1/30) <- 30fps

/* Ball Values */
extern glm::vec3 positions[MAXN];	// Ball Positions
extern glm::vec3 velocity[MAXN];	// Ball Velocities
extern float mass[MAXN];			// Ball masses
extern float radius[MAXN];			// Ball Radii

extern int ic, jc;					// Index of collider balls
extern float tc;					// Time to collision
extern float tf;					// Time until next frame

void AdvanceToNextFrame();
void DeclareBalls();
void Initialize();
void Jump(float t);
float Predict();
bool Interfere(unsigned int i, unsigned int j);
float TimeToBounce(unsigned int i);
float TimeToCollision(unsigned int i, unsigned int j);
void ComputeVelocityAfterBounce(unsigned int i);
void ComputeVelocityAfterCollision(unsigned int i, unsigned int j);
void HandleCollisions();

void LogPositions();
void LogRadii();