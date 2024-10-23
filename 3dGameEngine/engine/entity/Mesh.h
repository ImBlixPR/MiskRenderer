#pragma once
//c++ header
#include <vector>

//opengl header
#include <GL/glew.h>

//my own header
#include "Entity_struct.h"


struct bufferObject {
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;

};

class Mesh {

public:

	//defualt constructor
	Mesh();

	//main constructor
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int>  indices);

	//things
	void initMesh();

	void DrawMesh();




	~Mesh();

private:
	std::vector<Vertex> mVertices;
	std::vector<unsigned int> mIndices;

	//buffers object
	bufferObject mBufferObj;



};


