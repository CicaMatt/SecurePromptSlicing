#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Image;

Image images[] = {"logo", "banner"};

int image_exists(char *image) {
    for (size_t i = 0; i < sizeof(images); i++) {
        if (strcmp(images[i].name, image) == 0) return 1;
    }
    return 0;
}

int main(void) {
    char *image = "logo";
    if (image_exists(image)) {
        printf("The file exists");
    } else {
        printf("The file does not exist");
    }
}