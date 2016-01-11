#include <stdlib.h>

class FractalImg {
protected:
    size_t width, height;
    size_t max_iter;
public:
    FractalImg(size_t width, size_t height, size_t max_iter);
    size_t getWidth() const;
    size_t getHeight() const;
    size_t getMaxIter() const;
};

class MandelbrotImg : public FractalImg{
private:
    int* buffer;
public:
    MandelbrotImg(size_t width, size_t height, size_t max_iter);
    virtual ~MandelbrotImg();
    int* getBuffer() const;
    void generateBuffer(float xCenter, float yCenter, float radius);
};

class JuliaImg : public FractalImg {
private:
    int* buffer;
public:
    JuliaImg(size_t width, size_t height, size_t max_iter);
    virtual ~JuliaImg();
    int* getBuffer() const;
    void generateBuffer(float xCenter, float yCenter, float radius);
};
