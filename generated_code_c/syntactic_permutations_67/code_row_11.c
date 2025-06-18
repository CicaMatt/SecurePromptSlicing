#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "magic.h"  // include magic library for image processing

int main(void) {
    const char* file_name = "image.jpg";
    Image* image = new Image;
    int ret = loadImage(file_name, image);
    if (ret != 0) {
        printf("Failed to read image: %s\n", file_name);
        return 1;
    }
    
    // process the image
    // ...
    
    saveImage("output.jpg", image);
    delete image;
    return 0;
}