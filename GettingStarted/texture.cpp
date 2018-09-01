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

void Texture::load_texture(unsigned char* image, int t_width, int t_height, int nr_channels)
{	
	this->data = image;
	this->img_format = nr_channels == 3 ? GL_RGB : GL_RGBA;
	this->int_format = nr_channels == 3 ? GL_RGB : GL_RGBA;
	this->width = t_width;
	this->height = t_height;

	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexImage2D(GL_TEXTURE_2D, 0, this->int_format, t_width, t_height, 0, this->img_format, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max);	
	
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);	
}