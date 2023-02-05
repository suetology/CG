#include "Events.h"

#include <iostream>

#include <GLFW/glfw3.h>

bool *Events::keys;
unsigned int *Events::frames;
unsigned int Events::currentFrame;
glm::vec2 Events::mousePosition;
glm::vec2 Events::mouseDelta;

int Events::Init()
{
	currentFrame = 0;
	mousePosition = glm::vec2(0.0f);
	mouseDelta = glm::vec2(0.0f);

	keys = new bool[BUTTONS];
	frames = new unsigned[BUTTONS];

	memset(keys, false, sizeof(bool) * BUTTONS);
	memset(frames, 0, sizeof(unsigned int) * BUTTONS);

	return 0;
}

void Events::Shutdown()
{
	free(keys);
	free(frames);
}

void Events::OnUpdate()
{
	mouseDelta = glm::vec2(0.0f);
	currentFrame++;
}

bool Events::GetKey(int key)
{
	return keys[key];
}

bool Events::GetKeyDown(int key)
{
	return keys[key] && frames[key] == currentFrame;
}

bool Events::GetKeyUp(int key)
{
	return !keys[key] && frames[key] == currentFrame;
}

bool Events::GetMouseButton(int button)
{
	return keys[KEYS + button];
}

bool Events::GetMouseButtonDown(int button)
{
	return keys[KEYS + button] && frames[KEYS + button] == currentFrame;
}

bool Events::GetMouseButtonUp(int button)
{
	return !keys[KEYS + button] && frames[KEYS + button] == currentFrame;
}