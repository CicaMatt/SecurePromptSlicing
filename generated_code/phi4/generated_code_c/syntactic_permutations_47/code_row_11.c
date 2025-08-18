#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
int handle_request(const char *url);
void send_file_to_browser(const char *filename);

// Decorator-like function to check URL and trigger appropriate handler
void url_handler(const char *url) {
    if (strcmp(url, "/get-file") == 0) {
        int result = handle_request(url);
        if (result == 1) {
            printf("File sent successfully.\n");
        } else {
            printf("File not found.\n");
        }
    } else {
        printf("Invalid URL.\n");
    }
}

// Function to check file existence and send it
int handle_request(const char *url) {
    const char *filename = "example.txt"; // Filename to check

    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        send_file_to_browser(filename);
        return 1;
    } else {
        return 0;
    }
}

// Function to simulate sending file to browser
void send_file_to_browser(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        printf("Sending %s to browser...\n", filename);
        // Simulating reading and sending the file content
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file)) {
            printf("%s", buffer);  // In real scenario, this would be sent over a network
        }
        fclose(file);
    }
}

int main() {
    const char *url = "/get-file";  // Example URL to trigger the handler

    url_handler(url);

    return 0;
}