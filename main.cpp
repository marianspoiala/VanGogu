#include <iostream>
#include <fstream>

#include "PngImageWriter.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./fractal-gen ./images/image!\n";
        return -1;
    }
    std::ifstream no_fin("numbers.txt");

    size_t img_width = 1280;
    size_t img_height = 720;
    size_t max_iter = 4096; 

    float radius = 0.0001;
    float xCenter = -0.802;
    float yCenter = -0.177;
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
