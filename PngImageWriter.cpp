#include <iostream>

#include "PngImageWriter.h"

PngImageWriter::PngImageWriter(const std::string& filename) : filename(filename) {
}

int PngImageWriter::write(const MandelbrotImg& img) {
    // TODO
    int exit_code = 0;
    FILE* fout;
    png_structp png_struct_ptr;
    png_infop png_info_ptr;
    png_bytep img_line_rgb;

    // Open the file for writing
    fout = fopen(filename.c_str(), "wb");
    if (!fout) {
        std::cout << "Could not open file for writing!\n";
        exit_code = -1;
    }
    
    // initialize a writing structure
    png_struct_ptr = png_create_write_struct(
            PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_struct_ptr) {
        std::cout << "Could not allocate a writing structure!\n";
        exit_code = -2;
    }

    // initialize info structure
    png_info_ptr = png_create_info_struct(png_struct_ptr);
    if (!png_info_ptr) {
        std::cout << "Could not allocate an info structure!\n";
        exit_code = -3;
    }

    // Setup exception handling
    if (setjmp(png_jmpbuf(png_struct_ptr))) {
        std::cout << "Error during png creation!\n";
        exit_code = -4;
    }

    // assign the output file to write in
    png_init_io(png_struct_ptr, fout);

    // PNG header
    png_set_IHDR(png_struct_ptr, png_info_ptr, img.getWidth(), img.getHeight(),
            8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_struct_ptr, png_info_ptr);
    img_line_rgb = (png_bytep) malloc(3 * img.getWidth() * sizeof(png_byte));

    const int* buffer = img.getBuffer();
    for (size_t j = 0; j < img.getHeight(); ++j) {
        for (size_t i = 0; i < img.getWidth(); ++i) {
           setPixelValues(&img_line_rgb[3*i], buffer[j * img.getWidth() + i],
             img.getMaxIter());
        }
        png_write_row(png_struct_ptr, img_line_rgb);
    }

    png_write_end(png_struct_ptr, NULL);

    fclose(fout);
    png_free_data(png_struct_ptr, png_info_ptr, PNG_FREE_ALL, -1);
    png_destroy_write_struct(&png_struct_ptr, (png_infopp)NULL);
    free(img_line_rgb);
    return exit_code;
}

int PngImageWriter::write(const JuliaImg& img) {
    // TODO
    return 0;
}

void PngImageWriter::setPixelValues(png_byte* pixel, int value, int max_iter) {
    // Modify this function to define color;
    if (value == max_iter) {
        pixel[0] = pixel[1] = pixel[2] = 0;
    } else if (value < 64) {
        pixel[0] = value * 2;
        pixel[1] = pixel[2] = 0;
    } else if (value < 128) {
        pixel[0] = (((value - 64) * 128) / 126) + 128;
        pixel[1] = pixel[2] = 0;
    } else if (value < 256) {
        pixel[0] = (((value - 128) * 62) / 127) + 193;
        pixel[1] = pixel[2] = 0;
    } else if (value < 512) {
        pixel[0] = 255;
        pixel[1] = (((value - 256) * 62) / 255) + 1;
        pixel[2] = 0;
    } else if (value < 1024) {
        pixel[0] = 255;
        pixel[1] = (((value - 512) * 63) / 511) + 64;
        pixel[2] = 0;
    } else {
        pixel[0] = pixel[1] = 255;
        pixel[2] = 0;
    }
}
