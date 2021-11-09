#include "Window.h"

#include <iostream>

int Window::width = 800;
int Window::height = 800;

Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
    Window::width = width;
    Window::height = height;
    // New window object, width 800, height 600, Titled LearnOpenGL, last two parameters irrelevant
    window = glfwCreateWindow(Window::width, Window::height, title, monitor, share);

    // Catch if window fails to open
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    // Registers the resize function for object window to framebuffer_size_callback
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share, GLFWframebuffersizefun callback)
{
    Window::width = width;
    Window::height = height;
    // New window object, width 800, height 600, Titled LearnOpenGL, last two parameters irrelevant
    window = glfwCreateWindow(width, height, title, monitor, share);

    // Catch if window fails to open
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    // Registers the resize function for object window to framebuffer_size_callback
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, callback);
}

// OpenGL will automatically call this function to resize the window
void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    if (width < height) 
    {
        glViewport(0, 0, (GLint)width, (GLint)width);
    }
    else
    {
        glViewport(0, 0, (GLint)height, (GLint)height);
    }
}

void Window::terminateWindow()
{
    glfwDestroyWindow(window);
}

void Window::makeContextCurrent()
{
    glfwMakeContextCurrent(window);
}

void Window::newFrame()
{
    glfwSwapBuffers(window);
}

void Window::setBackgroundColor(float r1, float g1, float b1, float a1)
{
    bgCol[0] = r1;
    bgCol[1] = g1;
    bgCol[2] = b1;
    bgCol[3] = a1;
}

void Window::clearScreen()
{
    glClearColor(bgCol[0], bgCol[1], bgCol[2], bgCol[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}