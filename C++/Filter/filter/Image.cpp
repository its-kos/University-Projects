#include "Image.h"
#include <iostream>
#include "ppm.h"

Image::Image(const Image& src) :Array2D<Color>(src){}

Image::Image(unsigned int width, unsigned height):Array2D<Color>(width, height, 0){}

bool Image::load(const std::string& filename, const std::string& format) {

	if (format == "ppm") {
		int w, h;
		float* im_p = image::ReadPPM(filename.c_str(), &w, &h);

		if (im_p == nullptr) {
			delete[]im_p;
			return false;
		}

		this->width = w;
		this->height = h;
		this->buffer.clear();
		for (int i = 0; i < width * height * 3; i+=3) {
			Color c(im_p[i], im_p[i + 1], im_p[i + 2]);
			this->buffer.push_back(c);
		}

		delete[]im_p;
		return true;

	}else {
		std::cout << "Only ppm images are supported as of now. \n";
		return false;
	}
}

bool Image::save(const std::string& filename, const std::string& format) {
	const char* path = filename.c_str();
	if (format == "ppm") {
		return image::WritePPM((float*)buffer.data(), width, height, path);
	}else {
		std::cout << "Only ppm images are supported as of now. \n";
		return false;
	}
}