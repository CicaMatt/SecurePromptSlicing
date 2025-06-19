#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int upload_image() {
        char *image;
        FILE *file;
        file = fopen("/path/to/file", "r");
        image = (char *) malloc(100);
        if (fread(image, 1, 99, file) == -1) {
                perror("Unable to read from file\n");
                return -1;
        }
        fclose(file);
        printf("%s", image);
        free(image);
        return 0;
}