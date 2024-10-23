#pragma once

#pragma once

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW\glfw3.h>

struct monitor {
	int monitorX;
	int monitorY;
	int monitorW;
	int monitorH;
};

class MyWindow
{
public:
	MyWindow();

	MyWindow(GLint windowWidth, GLint windowHeight);

	int Initialise();

	GLint getBufferWidth() { return bufferWidth; }
	GLint getBufferHeight() { return bufferHeight; }

	void CenterWindow();
	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	bool* getsKeys() { return keys; }

	void ClearWindow();

	GLfloat getXChange();
	GLfloat getYChange();

	void DisableMouse(bool flag = false);

	void swapBuffers() { glfwSwapBuffers(mainWindow); }



	~MyWindow();

private:
	GLFWwindow* mainWindow;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	//monitor stuff
			//monitor work area call back
	
	monitor myMonitor;


	bool keys[1024];

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;

	void createCallBacks();

	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};

