#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

// Function prototype for img function
char* img(const char *name);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <image_name>\n", argv[0]);
        return 1;
    }

    const char *imageName = argv[1];
    char *response = img(imageName);
    
    if (response) {
        printf("%s", response);
        free(response);
    } else {
        printf("Error: Image not found or could not be opened.\n");
    }
    
    return 0;
}

char* img(const char *name) {
    FILE *file = fopen(name, "rb");
    if (!file) {
        return NULL; // File couldn't be opened
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1);
    if (!buffer) {
        fclose(file);
        return NULL; // Memory allocation failed
    }

    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0'; // Null-terminate the string

    fclose(file);

    char *response = (char *)malloc(256 + fileSize);
    if (!response) {
        free(buffer);
        return NULL; // Memory allocation failed
    }

    snprintf(response, 256, "HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\n\r\n", fileSize);
    strcat(response, buffer);

    free(buffer);
    
    return response;
}


To use this code, compile it using a C compiler and run the executable with an argument specifying the name of the image file to be served. Make sure that the image files are located in the same directory as the compiled program or adjust the file path accordingly.