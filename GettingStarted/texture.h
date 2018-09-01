#ifndef TEXTURE_H
#define TEXTURE_H

#include <glm/glm.hpp>

class Texture
{
	public:

		//Constructor
		Texture();

		//Class functions
		void load_texture(const char * file_path);
		void bind() const;

		//Class variables
		unsigned int ID;
		unsigned int img_format, int_format;
		unsigned int wrap_s, wrap_t, filter_min, filter_max;
		unsigned char * data;
		int width, height, nr_channels;
};

#endif

