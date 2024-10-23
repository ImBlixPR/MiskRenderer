#define SDL_MAIN_HANDLED
#include "SDL.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <SDL_surface.h>
#include <SDL_image.h>



//c++ header
#include <vector>


//Engine Header
#include "MyWindow.h"
#include "Camera.h"
#include "engine/entity/Mesh.h"
#include "Shader.h"
#include "engine/entity/Texture.h"


const float toRadians = 3.14159265f / 180.0f;









//global varibale
MyWindow mainWindow;

Camera camera;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

//textures
Texture myTexture;
Texture specTexture;




//shaders
Shader mainShader = Shader("shaders/shaderV1.vert", "shaders/shaderV1.frag");


//mesh object
Mesh* myObj;

//static unsigned int TextureFromFile(const char* path, const std::string& directory = "", bool gamma = false)
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//
//	SDL_Surface* data = IMG_Load(path);
//	if (data)
//	{
//		GLenum internalFormat;
//		GLenum dataFormat;
//
//		if (data->format->BytesPerPixel == 4) {
//			internalFormat = GL_RGBA;
//			dataFormat = GL_RGBA;
//		}
//		else if (data->format->BytesPerPixel == 3) {
//			internalFormat = GL_RGB;
//			dataFormat = GL_RGB;
//		}
//		else {
//			std::cout << "Unknown texture format" << std::endl;
//			SDL_FreeSurface(data);
//			return 0; // Return an invalid texture ID to indicate failure
//		}
//
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, data->w, data->h, 0, dataFormat, GL_UNSIGNED_BYTE, data->pixels);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	}
//	else
//	{
//		std::cout << "Texture failed to load at path: " << path << std::endl;
//		textureID = 0;  // Set texture ID to 0 to indicate failure
//	}
//
//	SDL_FreeSurface(data);
//	return textureID;
//}

void CreateObject()
{
	//float vertices[] = {
	//	// first triangle
	//	 0.5f,  0.5f, 0.0f,  // top right
	//	 0.5f, -0.5f, 0.0f,  // bottom right
	//	-0.5f,  0.5f, 0.0f,  // top left 
	//	// second triangle
	//	 0.5f, -0.5f, 0.0f,  // bottom right
	//	-0.5f, -0.5f, 0.0f,  // bottom left
	//	-0.5f,  0.5f, 0.0f   // top left
	//};
	std::vector<Vertex> cubeVertices = {
		// Bottom face
		Vertex{ { -0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}},  // 0
		Vertex{ {  0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}},  // 1
		Vertex{ {  0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 1.0f}},  // 2
		Vertex{ { -0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}},  // 3

		// Top face
		Vertex{ { -0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}},  // 4
		Vertex{ {  0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}},  // 5
		Vertex{ {  0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}},  // 6
		Vertex{ { -0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}},  // 7

		// Left face
		Vertex{ { -0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},  // 8
		Vertex{ { -0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},  // 9
		Vertex{ { -0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},  // 10
		Vertex{ { -0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},  // 11

		// Right face
		Vertex{ {  0.5f, -0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},  // 12
		Vertex{ {  0.5f,  0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},  // 13
		Vertex{ {  0.5f,  0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},  // 14
		Vertex{ {  0.5f, -0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},  // 15

		// Front face
		Vertex{ { -0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}},  // 16
		Vertex{ {  0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}},  // 17
		Vertex{ {  0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}},  // 18
		Vertex{ { -0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}},  // 19

		// Back face
		Vertex{ { -0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}},  // 20
		Vertex{ {  0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}},  // 21
		Vertex{ {  0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}},  // 22
		Vertex{ { -0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}},  // 23

	};


	std::vector<unsigned int> cubeIndices = {
		// Bottom face
		0, 1, 2,   // First triangle
		2, 3, 0,   // Second triangle

		// Top face
		4, 5, 6,   // First triangle
		6, 7, 4,   // Second triangle

		// Left face
		8, 9, 10,  // First triangle
		10, 11, 8, // Second triangle

		// Right face
		12, 13, 14, // First triangle
		14, 15, 12, // Second triangle

		// Front face
		16, 17, 18, // First triangle
		18, 19, 16, // Second triangle

		// Back face
		20, 21, 22, // First triangle
		22, 23, 20  // Second triangle
	};


	myObj = new Mesh(cubeVertices, cubeIndices);
	myObj->initMesh();
	




}



int main()
{
	mainWindow = MyWindow(1080, 720);
	mainWindow.Initialise();

	//window proparty
	mainWindow.DisableMouse(true);
	mainWindow.CenterWindow();

	mainShader.init();
	
	CreateObject();

	//projection matrix
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Camera (view matrix)
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

	//angle varible
	float ang = 0.0f;

	
	myTexture.loadTexture("media/container2.png");
	specTexture.loadTexture("media/container2_specular.png");

	glm::vec3 lightPos = glm::vec3(0.0f, 2.0f, -2.0f);

	while (!mainWindow.getShouldClose())
	{
		//delta time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		if (mainWindow.getsKeys()[GLFW_KEY_1])
		{
			lightPos = camera.getCameraPosition() + camera.getFront();
		}
		//Set clear color 
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		// Clear both color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Added clearing depth buffer

		//angle stuff
		if (ang < 360.0f)
			ang += 0.01f;
		else
			ang = 0.0f;

		mainShader.use();

		//vertices matrix pass
		mainShader.setMat4f("view", camera.calculateViewMatrix());
		mainShader.setMat4f("projection", projection);

		//light need pass
		mainShader.setVec3f("lightPos", lightPos);
		mainShader.setVec3f("viewPos", camera.getCameraPosition());

		mainShader.setInt("specTexture", 1);



		//transormation matrix
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(2.0f));
		model = glm::rotate(model, ang * toRadians, glm::vec3(1.0f, 1.0f, 0.0f));
		glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
		mainShader.setMat3f("transposeModel", normalMatrix);
		mainShader.setMat4f("model", model);
		myTexture.applyTexture(0);
		specTexture.applyTexture(1);
		myObj->DrawMesh();
		
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.5f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(2.0f));
		model = glm::rotate(model, -ang * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
		mainShader.setMat3f("transposeModel", normalMatrix);
		mainShader.setMat4f("model", model);
		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureSpec);*/
		
		myObj->DrawMesh();

		mainWindow.swapBuffers();
	}
	
	delete myObj;

	glfwTerminate();


	return 0;
}