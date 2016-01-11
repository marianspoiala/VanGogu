rm ./images/*.png
make clean
make build
make run

cd images
time convert -reverse -delay 40 -loop 0 *.png fractal.gif
mv fractal.gif ..
cd ..
