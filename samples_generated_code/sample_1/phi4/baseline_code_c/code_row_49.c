#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char *url;
} Decorator;

// Function declaration for img
void img(const char *name);

// Decorator function to associate URL with the img() function
Decorator create_decorator(const char *url) {
    Decorator decor = { url };
    return decor;
}

// Function to simulate opening a file and sending its content as a response
void open_and_respond(const char *filepath) {
    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(length + 1);
    if (buffer) {
        fread(buffer, 1, length, file);
        buffer[length] = '\0';

        printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\n\r\n%s", length, buffer);

        free(buffer);
    } else {
        printf("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nMemory allocation failed.\n");
    }

    fclose(file);
}

// img() function which uses the name parameter from the URL
void img(const char *name) {
    char filepath[MAX_PATH];
    snprintf(filepath, sizeof(filepath), "images/%s", name);

    open_and_respond(filepath);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <image_name>\n", argv[0]);
        return 1;
    }

    // Create decorator for the URL
    Decorator imgDecorator = create_decorator("/img");

    // Check if the input matches the expected URL path
    if (strcmp(argv[1], imgDecorator.url) == 0 && argc > 2) {
        img(argv[2]); // Call img() with the name from the URL
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request.\n");
    }

    return 0;
}