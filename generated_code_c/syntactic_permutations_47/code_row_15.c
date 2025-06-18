#include <stdio.h> 
#include <stdlib.h>  
#include <string.h>

void send_image(char *imageName) {
    FILE *fp = fopen(imageName, "rb");
    char buff[256];
    while (fread(buff, sizeof(char), 256, fp)) {
        printf("%s", buff);
    }
}

void check_image(char *imageName) {
    FILE *fp = fopen("images/", "r");
    if (!fp) {
        printf("Image does not exist\n");
        return;
    }
    send_image(imageName);
}

int main() {
    char image[] = {"image1.jpg"};
    check_image(image);
    return 0;
}