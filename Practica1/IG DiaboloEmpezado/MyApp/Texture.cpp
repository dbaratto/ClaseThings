#include "Texture.h"


Texture::~Texture()
{
}

void Texture::init() {
	glGenTextures(1, &id);

	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, id);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV, GL_REPLACE);
}

bool Texture::load(const std::string & BMP_Name, GLubyte alpha) {
	if (id == 0)
	{
		init();
	}

	PixMap32RGBA pixMap;

	pixMap.load_bmp24BGR(BMP_Name);



	if (alpha != 255) {
		pixMap.set_alpha(alpha);
	}

	w = pixMap.width();

	h = pixMap.height();

	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixMap.data());

	return true;
}