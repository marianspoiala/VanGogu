# VanGogu
Create an image just using fractal geometry.(http://elf.cs.pub.ro/mps/wiki/proiect/proiect-2).


Igescu Maria, 341C1, maria.igescu@gmail.com (team leader)          
Ambarus Gabriel, 342C1, gabi_ambarus@yahoo.com  (dev giff)         
Puschila Daniel, 342C4, daniel.puschila@gmail.com (dev)       
Suciu Andrei, 342C5, andreicorneliu.suciu@gmail.com (technical writer)  
Spoiala Marian, 342C5, spoialamarian@gmail.com  (dev)        
Avram Florin, 342C3, avram.florin.c@gmail.com (dev, analist)        
Gavril Alexandru, 341C4, alexandru.gavril.florin@gmail.com (dev)

------------------------------------------------------------------------

* **To run** the application just run the script video-gen.sh

* **To modify** the colors of the images modify the values in the function:
    PngImageWriter.cpp => **setPixelValues**
This function works as follows:
    value = iterations made for that pixel
    max_iter = maximum number of iterations for that pixel
    pixel = (R, G, B) pixel

    Modify (R, G, B) values from the iterations number made for that pixel.


* For the application **to work** you will need to install the following packages:
    * sudo apt-get install libpng*
    * sudo apt-get install imageMagick

* Be sure to use gcc-4.7 and g++-4.7 - 

Tutorial install gcc : http://askubuntu.com/questions/113291/how-do-i-install-gcc-4-7
