rm ./images/*.png
make clean
make build
make run
mencoder mf://images/*.png -mf w=1280:h=720:fps=2:type=png -ovc x264 -x264encopts subq=6:partitions=all:8x8dct:me=umh:frameref=5:bframes=3:b_pyramid=normal:weight_b -o mandelbrot.avi
