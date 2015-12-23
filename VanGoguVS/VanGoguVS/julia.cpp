#include <complex>
#include "julia.h"
using namespace std;

unsigned int getJuliaIteration(generatorFunction f, std::complex<double> z, std::complex<double> c, double maxRange, unsigned int maxIterations) {
	for (unsigned int i = 0; i < maxIterations; i++) {
		z = f(z, c);
		if (abs(z) > maxRange)
			return i;
	}
	return maxIterations;
}