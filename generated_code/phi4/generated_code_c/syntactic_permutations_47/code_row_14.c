#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Function prototype for checking image existence
int checkImageExists(const char *filename);

// Decorator-like function to associate a URL with our file-checking function
void handleRequest(const char *url) {
    // Extract the filename from the URL (assuming URL is of form "/images/filename.ext")
    const char *prefix = "/images/";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        const char *filename = url + strlen(prefix);
        
        // Check if image exists
        int exists = checkImageExists(filename);

        if (exists) {
            printf("File %s exists.\n", filename);
        } else {
            printf("File %s does not exist.\n", filename);
        }
    } else {
        printf("URL is not for an image file.\n");
    }
}

// Function to check if the given file exists
int checkImageExists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

int main() {
    // Example usage
    handleRequest("/images/sample.jpg");

    return 0;
}