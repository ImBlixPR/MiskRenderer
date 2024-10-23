#include "MyWindow.h"

MyWindow::MyWindow()
{
	width = 800;
	height = 600;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}

	xChange = 0;
	yChange = 0;
}

MyWindow::MyWindow(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
	xChange = 0;
	yChange = 0;

}

int MyWindow::Initialise()
{
	//Initialise GLFW
	if (!glfwInit())
	{
		printf("GLFW initilisation failed!");
		glfwTerminate();
		return 1;
	}

	//setup GLFW window properties
	//OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Core profile = No Backwords Compataibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}

	//Get Buffer size information

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//Set context for GLEW to use 
	glfwMakeContextCurrent(mainWindow);

	//Handle keys press and release

	createCallBacks();
	//glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Allow modern extension
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialisation failed!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	//Setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);


}

void MyWindow::CenterWindow()
{
	int count;
	GLFWmonitor** tMonitors = glfwGetMonitors(&count);
	glfwGetMonitorWorkarea(tMonitors[0], &myMonitor.monitorX, &myMonitor.monitorY, &myMonitor.monitorW, &myMonitor.monitorH);
	//window location
	glfwSetWindowPos(mainWindow, (myMonitor.monitorW / 2) - (bufferWidth / 2), (myMonitor.monitorH / 2) - (bufferHeight / 2));
}

void MyWindow::createCallBacks()
{
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

void MyWindow::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	MyWindow* theWindow = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("Pressed: %d \n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("Released: %d \n", key);

		}

	}
}

void MyWindow::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	MyWindow* theWindow = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;

	//printf("x:%.6f , y:%.6f \n", theWindow->xChange, theWindow->yChange);
}

void MyWindow::ClearWindow()
{
	//Set clear color 
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	// Clear both color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Added clearing depth buffer
}

GLfloat MyWindow::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat MyWindow::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void MyWindow::DisableMouse(bool flag)
{
	if(flag)
		glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

MyWindow::~MyWindow()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

