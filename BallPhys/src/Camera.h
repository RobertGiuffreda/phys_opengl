#pragma once

#include "glm.hpp"

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

const float SPEED = 30.0f;
const float THETA = 90.0f;
const float PHI = 0.0f;

enum class Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	glm::vec3 pos;
	glm::vec3 gaze;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	// To describe camera direction
	float pitch;
	float yaw;
	
	// To describe position relative to center of container
	float phi;
	float theta;

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 wup = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH, float theta = THETA, float phi = PHI);
	Camera(float xpos, float ypos, float zpos, float xup, float yup, float zup, float yaw, float pitch);

	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoff, float yoff);
	void ProcessScroll(float offset);

	glm::mat4 GetViewMatrix();
private:
	void UpdateCameraVectors();
};