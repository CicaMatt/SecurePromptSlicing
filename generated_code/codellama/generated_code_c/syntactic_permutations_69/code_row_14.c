#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void upload_image(char* path) {
    FILE *file;
    char buffer[2048];
    
    if ((file = fopen(path, "w")) == NULL) {
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }
    
    while (fgets(buffer, 2048, stdin)) {
        if (strcmp(buffer, "\n") != 0) {
            fputs(buffer, file);
        }
    }
    
    fclose(file);
}