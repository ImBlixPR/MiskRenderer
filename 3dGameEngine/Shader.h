#pragma once
#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>



class Shader
{
public:
	Shader();

	Shader(const char* vShaderPath, const char* fShaderPath);


	void init();

	void use();

	void clearShader();
	~Shader();


public:
	//uniform set functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, GLuint value) const;
	void setFloat(const std::string& name, GLfloat value) const;
	void setVec3f(const std::string& name, glm::vec3 value) const;
	void setVec4f(const std::string& name, glm::vec4 value) const;
	void setMat4f(const std::string& name, glm::mat4 value) const;
	void setMat3f(const std::string& name, glm::mat3 value) const;


private:

	std::string vertexCode;
	std::string fragmentCode;

	unsigned int shaderId;

private:
	void addShader(std::string shaderCode, GLenum shaderType);
	
	std::string loadShaderCode(const char* path);
};

