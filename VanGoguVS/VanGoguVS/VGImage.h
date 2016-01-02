#pragma once

#include <string.h>
#include <stdlib.h>

#define PIXEL_SIZE sizeof(unsigned char) * 4

//Access (get/set) the red/green/blue/alpha component of a pixel of a image.
//No checks are performed, so it might crash if used wrong.
#define r(img, x, y) img.rawData[img.rowSize * y + x * PIXEL_SIZE]
#define g(img, x, y) img.rawData[img.rowSize * y + x * PIXEL_SIZE + sizeof(unsigned char)]
#define b(img, x, y) img.rawData[img.rowSize * y + x * PIXEL_SIZE + 2*sizeof(unsigned char)]
#define a(img, x, y) img.rawData[img.rowSize * y + x * PIXEL_SIZE + 3*sizeof(unsigned char)]


//Probably of no use. Ignore this class!
typedef struct pixel {
	unsigned char * r = nullptr;
	unsigned char * g = nullptr;
	unsigned char * b = nullptr;
	unsigned char * a = nullptr;
	bool isValid = false;

	inline bool operator==(pixel p) {
		if (p.r == r && p.g == g && p.b == b && p.a == a)
			return true;
		else
			return false;
	}

	inline pixel operator+(pixel p) {
		pixel result = pixel();
		result.a = p.a + *a;
		result.r = p.r + *r;
		result.g = p.g + *g;
		result.b = p.b + *b;
		return result;
	}

} Pixel;

class VGImage {
private:
	bool initialized = false;
	unsigned int width = 0;
	unsigned int height = 0;

public:
	unsigned char * rawData = nullptr;

	//Size (in bytes) of a row of pixels. Needed for "nicer" code.
	size_t rowSize = 0;

	//Default constructor. It constructs an "invalid" image! (Intentional error)
	//Don't try to use it to create valid images - it will set the created image
	//in an invalid state. It is also used to signal that an error occured while
	//constructing an image from something else (getSubImage).
	VGImage();

	//Constructor for general usage.
	VGImage(unsigned int x, unsigned int y);

	//TODO.
	static VGImage loadBMP(const char* fileName);

	//If something returned a VGImage that's not initialized, that means an error
	//occured and you shouldn't use the returned result.
	bool isInitialized();

	unsigned int getWidth();
	unsigned int getHeight();

	//Will return a subimage of the current image.
	/*

	(0,0) . . .   .   . . . . (9,0)
	.   . . .   .   . . . .   .
	.   . . . (4,2)---------(9,2)
	.   . . .   |   . . . .   |
	.   . . . (4,4)---------(9,4)

	Let's say you have a 10x5 pixels image. You want the bottom corner?
	startX = 4, startY = 2
	endX = 9, endY = 4

	It will return an unitialized VGImage if startX < endX or startX > width
	or obvious invalid input like that.
	*/
	VGImage getSubImage(unsigned int startX, unsigned int startY, unsigned int endX, unsigned int endY);

	//TODO
	void renderBMP(const char* fileName);

	//It's useless, it won't be used.
	Pixel getPixel(unsigned int x, unsigned int y);

	//Useless.
	bool setPixel(unsigned int r, unsigned int g, unsigned int b, unsigned int a, unsigned int x, unsigned int y);

	~VGImage();

	//Didn't want to include the math library just for this.
	int sgn(int n) {
		if (n < 0)
			return -1;
		else if (n > 0)
			return 1;
		return 0;
	}

	//TODO
	void resize(unsigned int newWidth, unsigned int newHeight);

	//Check the example. It's still incomplete. (repeat must always be true)
	//Basically it will shift the image on the horizontal / vertical plane and
	//fill the missing parts with the rest of the image. 
	void shift(int horizontal, int vertical, bool repeat, bool resize);

	//Adds every pixel on all the channels
	void add(VGImage image);
	void substract(VGImage image);
	void printImage();

	//Adds every pixel from the specified channel in current image
};
