#include "Window.h"

#include "Events.h"

GLFWwindow* Window::window;
int Window::width;
int Window::height;
float Window::aspectRatio;
const char* Window::title;
glm::vec3 Window::backgroundColor;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        Events::keys[key] = true;
        Events::frames[key] = Events::currentFrame;
    }
    else if (action == GLFW_RELEASE)
    {
        Events::keys[key] = false;
        Events::frames[key] = Events::currentFrame;
    }
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    float x = static_cast<float>(xpos);
    float y = static_cast<float>(ypos);

    Events::mouseDelta.x = x - Events::mousePosition.x;
    Events::mouseDelta.y = Events::mousePosition.y - y;

    Events::mousePosition = glm::vec2(x, y);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        Events::keys[KEYS + button] = true;
        Events::frames[KEYS + button] = Events::currentFrame;
    }
    else if (action == GLFW_RELEASE)
    {
        Events::keys[KEYS + button] = false;
        Events::frames[KEYS + button] = Events::currentFrame;
    }
}

int Window::Init(const char* title, int width, int height, glm::vec3 backgroundColor)
{
    Window::title = title;
    Window::width = width;
    Window::height = height;
    Window::backgroundColor = backgroundColor;

    if (!glfwInit())
    {
        return -1;
    }

    if (Window::width != 0 && Window::height != 0)
    {
        window = glfwCreateWindow(Window::width, Window::height, title, NULL, NULL);
    }
    else
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        glfwGetMonitorWorkarea(monitor, NULL, NULL, &Window::width, &Window::height);
        window = glfwCreateWindow(Window::width, Window::height, Window::title, monitor, NULL);
    }

    aspectRatio = (float)Window::width / Window::height;

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetKeyCallback(window, key_callback);

    if (glewInit() != GLEW_OK)
    {
        return -1;
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 0;
}

bool Window::Opened()
{
	return !glfwWindowShouldClose(window);
}

void Window::OnUpdate()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
}

void Window::Close()
{
    if (!glfwWindowShouldClose(window))
    {
        glfwSetWindowShouldClose(window, 1);
    }
}

