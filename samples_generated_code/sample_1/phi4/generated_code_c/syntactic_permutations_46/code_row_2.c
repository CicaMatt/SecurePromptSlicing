#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate sending a file as a response
void send_file(FILE *file) {
    char buffer[1024];
    size_t bytes_read;
    
    // Simulate reading and sending the file content
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }
}

// Function to open a file given its name
FILE *open_image(const char *name) {
    FILE *file = fopen(name, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    return file;
}

// Decorator function to associate /img with the img() function
void handle_request(const char *path) {
    if (strncmp(path, "/img/", 5) == 0) {
        const char *name = path + 5; // Extract name from path
        FILE *file = open_image(name);
        send_file(file);
        fclose(file);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Simulate a request to the server
    const char *request_path = "/img/example.png";
    
    handle_request(request_path);
    
    return 0;
}