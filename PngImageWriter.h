#include <string>
#include <png.h>

#include "FractalsImg.h"

class PngImageWriter {
public:
    PngImageWriter(const std::string& filename);
    int write(const MandelbrotImg& img);
    int write(const JuliaImg& img);
private:
    void setPixelValues(png_byte *pixel, int value, int max_iter);
    std::string filename;
};
