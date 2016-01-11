CXX=g++
CXXFLAGS=-Wall -g -std=c++11
LDDFLAGS=-lpng -lm

build: main.o PngImageWriter.o FractalsImg.o
	$(CXX) $(CXXFLAGS) -o fractal-gen main.o PngImageWriter.o FractalsImg.o $(LDDFLAGS)

main.o:
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

PngImageWriter.o: PngImageWriter.h
	$(CXX) $(CXXFLAGS) -c PngImageWriter.cpp -o PngImageWriter.o $(LDDFLAGS)

FractalsImg.o: FractalsImg.h
	$(CXX) $(CXXFLAGS) -c FractalsImg.cpp -o FractalsImg.o $(LDDFLAGS)

run:
	./fractal-gen ./images/image
clean:
	rm -rf *.o fractal-gen
