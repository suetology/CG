#pragma once

#include <glm/glm.hpp>

enum Direction
{
	UP = 0b000001,
	DOWN = 0b000010,
	FORWARD = 0b000100,
	BACK = 0b001000,
	RIGHT = 0b010000,
	LEFT = 0b100000
};

class Camera
{
private:
	glm::vec3 position;
	glm::vec3 up;
	glm::vec3 front;
	float fov;
	float yaw;
	float pitch;
	float rotationSensivity;
	float moveSpeed;

public:

	Camera(glm::vec3 position = glm::vec3(0.0f));

	inline glm::vec3 GetPosition() { return position; }

	inline void SetMoveSpeed(float speed) { moveSpeed = speed; }

	void Move();
	void Rotate();
	glm::mat4 GetLookAtMatrix();
	glm::mat4 GetPerspectiveMatrix();
};

