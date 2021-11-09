#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	GLFWwindow* window;

	Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share, GLFWframebuffersizefun callback);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void makeContextCurrent();
	void terminateWindow();
	void setBackgroundColor(float r, float g, float b, float a);
	void clearScreen();
	void newFrame();


private:
	float bgCol[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	static int width;
	static int height;
};

#endif