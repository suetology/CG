#pragma once

#include <glm/glm.hpp>

#define KEYS 1024
#define BUTTONS 1032

class Events
{
public:
	static int Init();
	static void Shutdown();
	static void OnUpdate();

	static bool GetKey(int key);
	static bool GetKeyDown(int key);
	static bool GetKeyUp(int key);

	static bool GetMouseButton(int button);
	static bool GetMouseButtonDown(int button);
	static bool GetMouseButtonUp(int button);

	static glm::vec2 GetMousePosition() { return mousePosition; }
	static glm::vec2 GetMouseDelta() { return mouseDelta; }

	static bool* keys;
	static unsigned int* frames;
	static unsigned int currentFrame;
	static glm::vec2 mousePosition;
	static glm::vec2 mouseDelta;
};

