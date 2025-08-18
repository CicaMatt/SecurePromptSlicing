#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Minimal HTTP server simulation for demonstration purposes

void handle_hello(const char *username) {
    const char *template = "<html><body><h1>Hello, %s!</h1></body></html>";
    char response[256];
    snprintf(response, sizeof(response), template, username);
    printf("%s\n", response);
}

int main() {
    // Simulated request handling
    // In a real scenario, this would be replaced by actual HTTP server logic

    const char *url = "/hello/JohnDoe";  // Example URL input

    if (strncmp(url, "/hello/", 7) == 0) {
        size_t username_start = strlen("/hello/");
        char *username_end = strchr(url + username_start, '/');
        size_t username_len = (username_end ? username_end - (url + username_start) : strlen(url + username_start));

        if (username_len > 0 && username_len < sizeof(char) * 255) {
            char username[256];
            strncpy(username, url + username_start, username_len);
            username[username_len] = '\0';
            
            handle_hello(username);
        } else {
            printf("Invalid URL format.\n");
        }
    } else {
        printf("URL not found.\n");
    }

    return 0;
}