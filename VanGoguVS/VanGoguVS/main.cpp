#include "julia.h"
#include "VGImage.h"
#include <stdio.h>

/* Most common used function for generating Julia sets. */
Complex sampleFunction(Complex z, Complex c) {
	return z*z + c;
}

void testGenerator() {
	//Initialize a 100x100 image.
	VGImage img(100, 100);

	//Set the range from -1 to 1.
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			double xCoord = (j / 100 * 2) - 1;
			double yCoord = (i / 100 * 2) - 1;

			double color = getJuliaIteration(sampleFunction, Complex(xCoord, yCoord), Complex(1, 0), 2, 300);

			//Set up the image. Note the color normalization!
			//Ignore the compiler conversion warnings here.
			r(img, j, i) = color / 300 * 255;
			g(img, j, i) = color / 300 * 255;
			b(img, j, i) = color / 300 * 255;
			a(img, j, i) = 255;
		}
	}

	//No way to test it without BMP/RAW output. It will be done.
}

int main() {

	int width = 3;
	int height = 3;
	VGImage img(width, height);

	//FILL THE IMAGE
	int counter = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			img.rawData[i * PIXEL_SIZE * width + j * PIXEL_SIZE] = counter;
			img.rawData[i * PIXEL_SIZE * width + j * PIXEL_SIZE + sizeof(unsigned char)] = counter;
			img.rawData[i * PIXEL_SIZE * width + j * PIXEL_SIZE + 2 * sizeof(unsigned char)] = counter;
			img.rawData[i * PIXEL_SIZE * width + j * PIXEL_SIZE + 3 * sizeof(unsigned char)] = counter;
			counter++;
		}
	}


	img.shift(0, -1, true, true);
	r(img, 0, 0) = 5;

	VGImage img2(width, height);

	//FILL THE IMAGE
	counter = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			img2.rawData[i * PIXEL_SIZE * width + j * PIXEL_SIZE] = counter;
			img2.rawData[i * PIXEL_SIZE * width + j * PIXEL_SIZE + sizeof(unsigned char)] = counter;
			img2.rawData[i * PIXEL_SIZE * width + j * PIXEL_SIZE + 2 * sizeof(unsigned char)] = counter;
			img2.rawData[i * PIXEL_SIZE * width + j * PIXEL_SIZE + 3 * sizeof(unsigned char)] = counter;
			counter++;
		}
	}


	img2.shift(0, -1, true, true);
	r(img2, 0, 0) = 5;

	img.printImage();

	img2.printImage();
	img.substract(img2);
	img.printImage();
	testGenerator();
	int temp = 0;

	scanf("%i", &temp);
}