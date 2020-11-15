/* p3170065 : Konstantinos Katserelis*/


#include "ppm.h"
#include <iostream>
#include <string>
#include "Filter.h"

using namespace std;
using namespace image;

inline bool check(string str) {
	char* p;
	strtod(str.c_str(), &p);
	return *p == 0;
}

int main(int argc, char* argv[]) {

	string lastArg, imagePath, argument;
	float aR, aG, aB, cR, cG, cB, g;

	if (argc <= 2) {
		cout << "Error, no Image and/or Filters given" << endl;
		return 0;

	}else {
		lastArg = argv[argc - 1];
		if (lastArg.find(".ppm") == -1) {
			cout << "Error, no Image or wrong format (Only the ppm image format is supported)" << endl;
		}else {

			imagePath = lastArg;
			Image passedImage, newImage;

			passedImage.load(imagePath, "ppm");
			newImage = Image(passedImage);

			int i = 0;
			while(i < argc - 2) {

				argument = argv[++i];
				if (argument.compare("-f") != 0) {
					cout << "Error, expected a filter." << endl;
					return 0;
				}

				argument = argv[++i];
				if (argument.compare("linear") == 0){
					if ((check(argv[++i]) == 1) && (check(argv[i + 1]) == 1) && (check(argv[i + 2]) == 1) && (check(argv[i + 3]) == 1) && (check(argv[i + 4]) == 1) && (check(argv[i + 5]) == 1)){
						
						aR = stof(argv[i]);
						aG = stof(argv[i + 1]);
						aB = stof(argv[i + 2]);

						cR = stof(argv[i + 3]);
						cG = stof(argv[i + 4]);
						cB = stof(argv[i + 5]);

						FilterLinear* linear = new FilterLinear(aR, aG, aB, cR, cG, cB);

						cout << "Applying linear filter" << endl;
					    newImage = *linear << passedImage;
						
						i += 5;

					}else {
						cout << "Error, expected filter parameters." << endl;
						return 0;
					}

				}else if (argument.compare("gamma") == 0){

					if (check(argv[++i])) {

						g = stof(argv[i]);
						FilterGamma* gamma = new FilterGamma(g);

						cout << "Applying gamma filter" << endl;
						newImage = *gamma << passedImage;

					}else {
						cout << "Error, expected a filter parameter." << endl;
						return 0;
					}

				}else{
					cout << "Error, expected a filter name." << endl;
					return 0;
				}
			}

			const int pos = imagePath.find_last_of('\\');
			if (pos == -1) {

				const int pos = imagePath.find_last_of('/');
				if (pos == -1){
					imagePath.insert(0, "filtered_");
				}else {
					imagePath.insert(pos, "filtered_");
				}
			}else {
				imagePath.insert(pos, "filtered_");
			}

			cout << "Saving image: " + imagePath << endl;
			newImage.save(imagePath, "ppm");
			return 0;
		}
	}
}

