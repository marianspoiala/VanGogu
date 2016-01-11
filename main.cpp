#include <iostream>
#include <fstream>
#include <ctime>

#include "PngImageWriter.h"

float getrand() {
  static bool init = false;

  if (!init) {
    srand(time(NULL));
    init = true;
  }

  return ((float)rand() / (float)((unsigned)RAND_MAX + 1)); 
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./fractal-gen ./images/image!\n";
        return -1;
    }
    std::ifstream no_fin("numbers.txt");

    size_t img_width = 800;
    size_t img_height = 600;
    size_t max_iter = 1024; 

    float radius = 0.0001;
    /**
     * Good values for xCenter and yCenter are -0.802 and -0.177*
	 */

    float xCenter = -getrand();
    float yCenter = -getrand();

    while(xCenter >-0.79 || xCenter < -0.82)
    	xCenter = -getrand();
    while(yCenter >-0.16 || yCenter < -0.19)
    	yCenter = -getrand();
    printf("%f %f\n",xCenter,yCenter);
    int result = 0;

    // Create an image and generate the buffer for it.
    MandelbrotImg image(img_width, img_height, max_iter);
    while (no_fin >> radius) {
        std::string filename = argv[1];
        std::string id = std::to_string(radius);
        filename = filename + id + ".png";

        // start the writer and generate the buffer
        PngImageWriter img_writer(filename);
        image.generateBuffer(xCenter, yCenter, radius);
        result = img_writer.write(image);

        if (result < 0) {
            return result;
        } 
    }
    no_fin.close();
    return result;
}
