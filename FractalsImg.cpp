#include "FractalsImg.h"

#include <complex>
#include <png.h>

/* FractalImg implementation */
FractalImg::FractalImg(size_t width, size_t height, size_t max_iter) :
    width(width), height(height), max_iter(max_iter) {
}

size_t FractalImg::getWidth() const {
    return width;
}

size_t FractalImg::getHeight() const{
    return height;
}

size_t FractalImg::getMaxIter() const {
    return max_iter;
}

/* MandelbrotImg implementation */
MandelbrotImg::MandelbrotImg(size_t width, size_t height,
  size_t max_iter = 4096) : FractalImg(width, height, max_iter) {
    buffer = new int[width * height];  
}

MandelbrotImg::~MandelbrotImg() {
    delete[] buffer;
}

int* MandelbrotImg::getBuffer() const {
    return buffer;
}

void MandelbrotImg::generateBuffer(float xCenter, float yCenter, float radius) {
    for (size_t yPos = 0; yPos < height; yPos++) {
        float c_img = (yCenter - radius) + (2 * radius / height) * yPos;
        for (size_t xPos = 0; xPos < width; xPos++) {
            float c_real = (xCenter - radius) + (2 * radius / width) * xPos;

            float z_real = 0, z_img = 0;
            size_t iterations = 0;
            
            while (z_real * z_real + z_img * z_img <= 4 && iterations < max_iter) {
                float tmp = z_real * z_real - z_img * z_img + c_real;
                z_img = 2 * z_real * z_img + c_img;
                z_real = tmp;
                iterations++;
            }

            buffer[yPos * width + xPos] = iterations;
        }
    }
}

/* Julia implementation */
JuliaImg::JuliaImg(size_t width, size_t height, size_t max_iter = 4096) :
  FractalImg(width, height, max_iter) {
    buffer = new int[width * height];
}

JuliaImg::~JuliaImg() {
    delete[] buffer;
}

void JuliaImg::generateBuffer(float xCenter, float yCenter, float radius) {
    // TODO
}

int* JuliaImg::getBuffer() const {
    return nullptr;
}
