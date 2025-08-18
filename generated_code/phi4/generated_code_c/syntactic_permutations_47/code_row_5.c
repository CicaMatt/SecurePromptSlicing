#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGES_FOLDER "images/"
#define MAX_PATH_LENGTH 260

// Function to check if a file exists in the given directory
int file_exists(const char *filename) {
    char filepath[MAX_PATH_LENGTH];
    snprintf(filepath, sizeof(filepath), "%s%s", IMAGES_FOLDER, filename);
    
    FILE *file = fopen(filepath, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

// Function to send the file to the browser
void send_file_to_browser(const char *filename) {
    // This is a placeholder for sending the file over a network socket
    // In a real application, you would use networking libraries like sockets to handle this
    printf("Sending '%s' to the browser...\n", filename);
}

int main() {
    char filename[] = "example.jpg";  // Replace with dynamic input in practice
    
    if (file_exists(filename)) {
        send_file_to_browser(filename);
    } else {
        printf("File does not exist.\n");
    }

    return 0;
}