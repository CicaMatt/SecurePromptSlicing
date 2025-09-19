#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Function to simulate sending a file content as HTTP response
void send_response(FILE *file) {
    char buffer[BUFFER_SIZE];
    size_t bytesRead;
    
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\n");
        return;
    }
    
    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\n\r\n");
    
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }
}

// Decorator function to extract the name from URL and open the corresponding file
void img(const char *url) {
    const char *prefix = "/img/";
    size_t prefix_len = strlen(prefix);
    
    if (strncmp(url, prefix, prefix_len) == 0) {
        // Get the filename after /img/
        const char *filename_start = url + prefix_len;
        
        // Open the file from images directory
        FILE *file = fopen(strcat("/images/", filename_start), "rb");
        
        if (file != NULL) {
            send_response(file);
            fclose(file);
        } else {
            printf("HTTP/1.1 404 Not Found\r\n");
        }
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);

    return EXIT_SUCCESS;
}