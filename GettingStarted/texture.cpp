#include <iostream>

#include <glad/glad.h>

#include "texture.h"
#include "stb_image.h"

Texture::Texture()
	:width(0), height(0), int_format(GL_RGB), img_format(GL_RGB), wrap_s(GL_REPEAT), wrap_t(GL_REPEAT), filter_min(GL_LINEAR), filter_max(GL_LINEAR)
{
	glGenTextures(1, &this->ID);
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}

void Texture::load_texture(const char * file_path)
{	
	int twidth, theight, nr_channels;
	this->data = stbi_load(file_path, &twidth, &theight, &nr_channels, 0);
	this->img_format = nr_channels == 3 ? GL_RGB : GL_RGBA;
	this->int_format = nr_channels == 3 ? GL_RGB : GL_RGBA;
	this->width = twidth;
	this->height = theight;

	glBindTexture(GL_TEXTURE_2D, this->ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, this->int_format, twidth, theight, 0, this->img_format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture " << file_path << std::endl;
	}
	
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);	
}