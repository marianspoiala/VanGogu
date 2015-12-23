#pragma once

#include "VGImage.h"

VGImage::VGImage() {
	// An invalid image.
	this->initialized = false;
}

VGImage::VGImage(unsigned int width, unsigned int height) {
	size_t totalSize = width * height * PIXEL_SIZE;
	this->rawData = (unsigned char*)malloc(totalSize);
	this->width = width;
	this->height = height;

	if (this->rawData == NULL) {
		// Init error occured. Too bad.
		this->initialized = false;
		return;
	}

	this->rowSize = PIXEL_SIZE * width;
	this->initialized = true;
}

VGImage::~VGImage() {
	if (this->initialized)
		free(this->rawData);
}

Pixel VGImage::getPixel(unsigned int x, unsigned int y) {
	Pixel result;
	if (this->initialized == false || x > this->width || y > this->height) {
		result.isValid = false;
	}
	else {
		result.r = this->rawData + y * this->rowSize + x * PIXEL_SIZE;
		result.g = this->rawData + y * this->rowSize + x * PIXEL_SIZE + sizeof(unsigned char);
		result.b = this->rawData + y * this->rowSize + x * PIXEL_SIZE + sizeof(unsigned char) * 2;
		result.a = this->rawData + y * this->rowSize + x * PIXEL_SIZE + sizeof(unsigned char) * 3;
		result.isValid = true;
	}
	return result;
}

unsigned int VGImage::getHeight() {
	if (this->initialized)
		return this->height;
	return 0;
}

unsigned int VGImage::getWidth() {
	if (this->initialized)
		return this->width;
	return 0;
}

bool VGImage::isInitialized() {
	return this->initialized;
}

VGImage VGImage::getSubImage(unsigned int startX, unsigned int startY, unsigned int endX, unsigned int endY) {
	// Sanity check.
	if (endX < startX || endY < startY || startX > this->width || endX > this->height || endX > this->width || endY > this->height)
		return VGImage();

	// Ok, everything's good.
	unsigned int resultWidth = endX - startX + 1;
	unsigned int resultHeight = endY - startY + 1;

	VGImage result = VGImage(resultWidth, resultHeight);

	size_t newRowSize = PIXEL_SIZE * resultWidth;
	unsigned char * rowCopyStart = this->rawData + startX;
	for (unsigned int i = 0; i < resultHeight; i++) {
		memcpy(result.rawData + newRowSize * i, rowCopyStart + this->rowSize * i, PIXEL_SIZE * resultWidth);
	}

	return result;
}

bool VGImage::setPixel(unsigned int r, unsigned int g, unsigned int b, unsigned int a, unsigned int x, unsigned int y) {
	//Sanity checks.
	if (r > 255 || g > 255 || b > 255 || a > 255)
		return false;

	if (x >= this->width || y >= this->height)
		return false;

	//Everything seems to be ok.
	unsigned char * pixelStart = this->rawData + y * this->rowSize + x * PIXEL_SIZE;
	*pixelStart = r;
	*(pixelStart + sizeof(unsigned char)) = g;
	*(pixelStart + 2 * sizeof(unsigned char)) = b;
	*(pixelStart + 3 * sizeof(unsigned char)) = a;

	return true;
}

void VGImage::shift(int horizontal, int vertical, bool repeat, bool resize) {
	if (repeat && !resize) {
		int horizontalShift = abs(horizontal) % this->width * sgn(horizontal);
		int verticalShift = abs(vertical) % this->height * sgn(vertical);

		//NORMALIZE!
		if (horizontalShift < 0)
			horizontalShift = this->width + horizontalShift;

		if (verticalShift < 0)
			verticalShift = this->height + verticalShift;

		unsigned char * tempRow = (unsigned char*)malloc(PIXEL_SIZE * this->width);

		for (unsigned int i = 0; i < this->height; i++) {

			unsigned char* startFrom = this->rawData + this->rowSize * i + PIXEL_SIZE * (this->width - horizontalShift);
			size_t sizeToCopy = horizontalShift * PIXEL_SIZE;

			memcpy(tempRow, startFrom, sizeToCopy);

			startFrom = this->rawData + this->rowSize * i;
			sizeToCopy = (this->width - horizontalShift) * PIXEL_SIZE;

			memcpy(tempRow + PIXEL_SIZE * horizontalShift, startFrom, sizeToCopy);
			memcpy(this->rawData + this->rowSize * i, tempRow, this->rowSize);
		}
		free(tempRow);

		//Time to shift on the vertical axis. With a buffer
		if (verticalShift) {
			size_t bufferSize = verticalShift * this->rowSize;
			unsigned char * buffer = (unsigned char*)malloc(bufferSize);

			memcpy(buffer, this->rawData, bufferSize);

			for (unsigned int i = 0; i < this->height - vertical; i++) {
				unsigned char * destination = this->rawData + i * this->rowSize;
				unsigned char * source = this->rawData + (this->height - i - 1) * this->rowSize;
				memcpy(destination, source, this->rowSize);
			}
			memcpy(this->rawData + (this->height - verticalShift) * this->rowSize, buffer, bufferSize);
			free(buffer);
		}
	}
}