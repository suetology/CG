#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window
{
public:
	static int Init(const char* title, int width, int height, glm::vec3 backgroundColor = glm::vec3(1.0f));
	static bool Opened();
	static void OnUpdate();
	static void Clear();
	static void Close();

	static inline GLFWwindow* Get() { return window; }
	static inline int GetWidth() { return width; }
	static inline int GetHeight() { return height; }
	static inline float GetAspectRatio() { return aspectRatio; }

	static inline void SetBackgroundColor(glm::vec3 color) { backgroundColor = color; }

private:
	static GLFWwindow* window;
	static int width, height;
	static float aspectRatio;
	static const char *title;
	static glm::vec3 backgroundColor;
};

