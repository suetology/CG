#include "Camera.h"

#include "Window.h"
#include "Events.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position)
	: position(position)
{
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	fov = 45.0f;
	yaw = -90.0f;
	pitch = 0.0f;
	moveSpeed = 1.0f;
	rotationSensivity = 1.0f;
}

void Camera::Move()
{
	int direction = 0;

	if (Events::GetKey(KEY_W))
	{
		direction += Direction::FORWARD;
	}
	if (Events::GetKey(KEY_S))
	{
		direction += Direction::BACK;
	}
	if (Events::GetKey(KEY_A))
	{
		direction += Direction::LEFT;
	}
	if (Events::GetKey(KEY_D))
	{
		direction += Direction::RIGHT;
	}
	if (Events::GetKey(KEY_LEFT_SHIFT))
	{
		direction += Direction::DOWN;
	}
	if (Events::GetKey(KEY_SPACE))
	{
		direction += Direction::UP;
	}

	if (direction & Direction::UP)
	{
		position.y += moveSpeed * 0.05f;
	}
	if (direction & Direction::DOWN)
	{
		position.y -= moveSpeed * 0.05f;
	}
	if (direction & Direction::FORWARD)
	{
		position += moveSpeed * front * 0.05f;
	}
	if (direction & Direction::BACK)
	{
		position -= moveSpeed * front * 0.05f;
	}
	if (direction & Direction::RIGHT)
	{
		position += moveSpeed * glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f))) * 0.05f;
	}
	if (direction & Direction::LEFT)
	{
		position -= moveSpeed * glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f))) * 0.05f;
	}
}

void Camera::Rotate()
{
	yaw += rotationSensivity * Events::GetMouseDelta().x * 0.1f;
	pitch += rotationSensivity * Events::GetMouseDelta().y * 0.1f;

	if (pitch > 89.0f)
		pitch = 89.0f;
	else if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(newFront);

	glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::cross(right, front);
}

glm::mat4 Camera::GetLookAtMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::GetPerspectiveMatrix()
{
	return glm::perspective(fov, static_cast<float>(Window::GetWidth()) / Window::GetHeight(), 0.1f, 100.0f);
}