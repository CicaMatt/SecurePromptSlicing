#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to escape special characters to HTML-safe sequences
char* escape(const char *input) {
    size_t len = strlen(input);
    char *output = malloc(len * 6 + 1); // Allocate maximum possible length
    if (!output) return NULL;

    output[0] = '\0';
    for (size_t i = 0; i < len; ++i) {
        switch (input[i]) {
            case '<': strcat(output, "&lt;"); break;
            case '>': strcat(output, "&gt;"); break;
            case '&': strcat(output, "&amp;"); break;
            case '"': strcat(output, "&quot;"); break;
            case '\'': strcat(output, "&#39;"); break;
            default: strncat(output, &input[i], 1); break;
        }
    }

    return output;
}

// Function to generate a hello message with an escaped username
char* hello(const char *username) {
    char *escaped_username = escape(username);
    if (!escaped_username) {
        return "Error: Unable to escape username.";
    }

    size_t buffer_size = strlen(escaped_username) + 20;
    char *message = malloc(buffer_size);
    if (!message) {
        free(escaped_username);
        return "Error: Memory allocation failed.";
    }

    snprintf(message, buffer_size, "Hello, %s!", escaped_username);
    free(escaped_username);

    return message;
}

// Function to handle the URL mapping and call hello() with the username
char* handle_request(const char *url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        const char *username_start = url + 7;
        return hello(username_start);
    }
    return "Error: Invalid URL.";
}

int main() {
    const char *test_url = "/hello/John<>&'";
    char *response = handle_request(test_url);

    printf("%s\n", response);
    free(response); // Free the allocated memory for the response

    return 0;
}