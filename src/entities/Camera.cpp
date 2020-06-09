#include "Camera.hpp"

void Camera::Update()
{
	direction = target - position;
	cameraZ = glm::normalize(position - target);
	cameraX = glm::normalize(glm::cross(up, cameraZ));
	cameraY = glm::normalize(glm::cross(cameraZ, cameraX));
}

void Camera::Rotate(float pitch, float yaw)
{
	glm::quat rotationX = glm::angleAxis(glm::radians(pitch), cameraX);
	glm::quat rotationY = glm::angleAxis(glm::radians(yaw), cameraY);
	glm::quat finalRotation = glm::normalize(glm::cross(rotationY, rotationX));
	direction = glm::rotate(finalRotation, direction);
	target = position + direction;
}

void Camera::MoveForward(float value)
{
	position += (-cameraZ * value);
	target += (-cameraZ * value);
}

void Camera::MoveBackward(float value)
{
	position += (cameraZ * value);
	target += (cameraZ * value);
}

void Camera::MoveLeft(float value)
{
	position += (-cameraX * value);
	target += (-cameraX * value);
}

void Camera::MoveRight(float value)
{
	position += (cameraX * value);
	target += (cameraX * value);
}

void Camera::MoveUp(float value)
{
	position += (cameraY * value);
	target += (cameraY * value);
}

void Camera::MoveDown(float value)
{
	position += (-cameraY * value);
	target += (-cameraY * value);
}
