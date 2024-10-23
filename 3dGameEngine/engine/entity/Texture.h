#pragma once

//opengl header


//c++ header
#include <iostream>
#include <filesystem>

struct Texture {


	unsigned int textureId;
	std::filesystem::path mFilePath;

	void loadTexture(const char* path);

	void applyTexture(unsigned int simplerNum);



};
