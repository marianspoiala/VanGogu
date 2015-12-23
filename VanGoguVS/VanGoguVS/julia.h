#pragma once
#include <complex>

typedef std::complex<double> Complex;

/*Ok, this is the prototype for a generator function.

Coder-friendly example:   Complex myFunction(Complex z, Complex c)

The most common function used in julia sets is z = z^2 + c
(equivalent to "return z*z + c;")

But it can be anything! (like sin(z)*cos(c)/ln(z*c) + cos(z)^2)

*/
typedef Complex(*generatorFunction)(Complex, Complex);

/*
This function returns the "color" of a point.
Variable z is the start variable (z0), variable c is the constant (although
not required to be strictly constant, you can vary it alongside the points of
the image).

Z should be the coordinates of the point that we want to compute (x = the real part,
y = the imaginary part). C is arbitrary. Max range is the "escape range" - use the
value "2" if you don't want to read about how fractals are generated.

MaxIterations - the higher the number, the more precise the fractal, the more time it
will take to compute.

Keep in mind the the returned color value will be in the range [0 - maxIterations], so
you might need to normalize it to [0, 255].

*/
unsigned int getJuliaIteration(generatorFunction f, Complex z, Complex c, double maxRange, unsigned int maxIterations);