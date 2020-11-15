#include "array2d.h"
#include "vec3.h"

using namespace math;

template <typename T>
const unsigned int Array2D<T>::getWidth() const {
	return width;
}

template <typename T>
const unsigned int Array2D<T>::getHeight() const {
	return height;
}

template <typename T>
T* Array2D<T>::getRawDataPtr() {
	return buffer;
}

template <typename T>
void Array2D<T>::setData(const T* const& data_ptr) {
	buffer.clear();
	for(int i = 0; i < width * height; i++) {
		buffer.push_back(*(data_ptr + i));
	}
}

template <typename T>
T& Array2D<T>::operator () (unsigned int x, unsigned int y) {
	return buffer.at(x + y * width);
}

template <typename T>
Array2D<T>::Array2D(unsigned int width, unsigned int height, const T* data_ptr ){
	this->width = width;
	this->height = height;
	if (data_ptr != nullptr) {
		for (int i = 0; i < (width * height); i++) {
			buffer.push_back(data_ptr[i]);
		}
	}else {
		Vec3<float> vector(0);
		for (int i = 0; i < (width * height); i++) {
			buffer.push_back(vector);
		}
	}
}

template <typename T>
Array2D<T>::Array2D(const Array2D& src){
	this->width = src.width;
	this->height = src.height;
	setData(src.buffer.data());
}

template <typename T>
Array2D<T>::~Array2D(){}

template <typename T>
Array2D<T>& Array2D<T>::operator = (const Array2D<T>& right){
	this->width = right.getWidth();
	this->height = right.getHeight();
	setData(right.buffer.data());
	return *this;
}