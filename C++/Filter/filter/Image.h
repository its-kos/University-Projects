#pragma once

#include <string.h>
#include <math.h>
#include "vec3.h"
#include "imageio.h"
#include "array2d.h"

typedef math::Vec3<float> Color;

class Image : public Array2D<Color>, public image::ImageIO{

	public:
		Image(const Image& src);
		Image(unsigned int width = 0, unsigned int height = 0);
		bool load(const std::string& filename, const std::string& format);
		bool save(const std::string& filename, const std::string& format);
};
