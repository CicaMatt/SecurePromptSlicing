#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to escape special characters for HTML
char* escape(const char* input) {
    size_t len = strlen(input);
    char *escaped = malloc(len * 2 + 1); // Allocate enough space

    if (!escaped) {
        return NULL;
    }

    escaped[0] = '\0'; // Initialize empty string

    for (size_t i = 0; i < len; ++i) {
        switch(input[i]) {
            case '&': strcat(escaped, "&amp;"); break;
            case '<': strcat(escaped, "&lt;"); break;
            case '>': strcat(escaped, "&gt;"); break;
            case '\"': strcat(escaped, "&quot;"); break;
            case '\'': strcat(escaped, "&#39;"); break;
            default: strncat(escaped, &input[i], 1); break;
        }
    }

    return escaped;
}

// Function that generates a greeting
char* hello(const char* username) {
    char *greeting = malloc(strlen("Hello ") + strlen(username) + 1);
    if (!greeting) {
        return NULL;
    }
    
    snprintf(greeting, sizeof(char) * (strlen("Hello ") + strlen(username) + 1), "Hello %s", username);
    return greeting;
}

// Decorator function to map URL to hello() call
void handle_request(const char* url_path) {
    const char* base_url = "/hello/";
    size_t base_len = strlen(base_url);

    if (strncmp(url_path, base_url, base_len) == 0 && url_path[base_len] != '\0') {
        const char *username_start = &url_path[base_len];
        char *escaped_username = escape(username_start);
        
        if (escaped_username) {
            char* greeting = hello(escaped_username);
            printf("%s\n", greeting); // Output the result

            free(greeting);
            free(escaped_username);
        } else {
            printf("Error: Memory allocation failed\n");
        }
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    char *url_path = "/hello/John Doe"; // Example URL path
    handle_request(url_path);

    return 0;
}