#include "ppm.h"
#include <string>
#include <fstream>
#include <iostream>

namespace image{
	float* ReadPPM(const char* filename, int* w, int* h) {

		int pos;
		int imageSize;
		int vals;
		float* imageArray;

		std::string line;
		std::ifstream reader;
		reader.open(filename, std::ios::in | std::ios::binary);
		reader >> line;

		if (!reader.is_open()) {
			std::cerr << "Problem with opening the file: " << filename << "\n";
			reader.close();
			return nullptr;
		}else {

			if (line == "p6" || line == "P6") {

				reader >> *w;
				reader >> *h;
				reader >> vals;

				imageSize = 3 * ((*w) * (*h));

				if (reader.fail()) {
					std::cerr << "Error reading header.\n";
					reader.close();
					return nullptr;
				}

				if (w < 0 || h < 0) {
					std::cerr << "Dimentions are smaller than 0.\n";
					reader.close();
					return nullptr;
				}else if (vals <= 0 || vals > 255) {
					std::cerr << "Wrong value range (Should be 255).\n";
					reader.close();
					return nullptr;
				}

				pos = reader.tellg();
				reader.seekg(pos + 1, 0);

				imageArray = new float[imageSize];
				char* temp = new char[imageSize];
				reader.read(temp, imageSize);

				for (int i = 0; i < imageSize; i++) {
					imageArray[i] = temp[i] / 255.0f;
				}

				reader.close();

				delete[] temp;
				return imageArray;

			}else {
				std::cerr << "Wrong Format\n";
				reader.close();
				return nullptr;
			}
		}
	}

	bool WritePPM(const float* data, int w, int h, const char* filename) {

		std::ofstream writer;
		writer.open(filename, std::ios::binary | std::ios::out);

		if (writer.fail()) {
			std::cerr << "Write process failed \n";
			writer.close();
			return false;
		}else {
			int size = 3 * h * w;
			char* normalizedData = new char[size];

			writer << "P6 \n" << w << " " << h << "\n" << "255\n";

			for (int i = 0; i < size; i++) {
				normalizedData[i] = data[i] * 255.0f;
			}

			writer.write(normalizedData, size);
			writer.close();

			delete[]normalizedData;
			return true;
		}
	}
}