#include "Texture.h"

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>

//Texture::Texture() : textureId(0)
//{
//	
//}Texture::Texture() : textureId(0)
//{
//	
//}

void Texture::loadTexture(const char* path)
{
	
	glGenTextures(1, &textureId);

	SDL_Surface* data = IMG_Load(path);
	if (data)
	{
		GLenum internalFormat;
		GLenum dataFormat;

		if (data->format->BytesPerPixel == 4) {
			internalFormat = GL_RGBA;
			dataFormat = GL_RGBA;
		}
		else if (data->format->BytesPerPixel == 3) {
			internalFormat = GL_RGB;
			dataFormat = GL_RGB;
		}
		else {
			std::cout << "Unknown texture format" << std::endl;
			SDL_FreeSurface(data);
			textureId = 0; // Return an invalid texture ID to indicate failure
		}

		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, data->w, data->h, 0, dataFormat, GL_UNSIGNED_BYTE, data->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		textureId = 0;  // Set texture ID to 0 to indicate failure
	}

	SDL_FreeSurface(data);
	std::cout << "texture id: " << textureId << "\n";
	

}

void Texture::applyTexture(unsigned int simplerNum)
{
	glActiveTexture(GL_TEXTURE0 + simplerNum);
	glBindTexture(GL_TEXTURE_2D, textureId);
}
