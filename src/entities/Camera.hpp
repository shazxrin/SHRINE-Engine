#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Camera
{
public:
	glm::vec3 cameraX;
	glm::vec3 cameraY;
	glm::vec3 cameraZ;
	glm::vec3 direction;
	glm::vec3 target;
	glm::vec3 position;
	glm::vec3 up;

	void Update();
	void Rotate(float pitch, float yaw);
	void MoveForward(float value);
	void MoveLeft(float value);
	void MoveRight(float value);
	void MoveBackward(float value);
};