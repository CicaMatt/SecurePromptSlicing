#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to convert special characters to HTML-safe sequences
char* escape(const char* input) {
    if (input == NULL) return NULL;
    
    size_t len = strlen(input);
    char *escaped = malloc((len * 2 + 1) * sizeof(char));
    if (!escaped) return NULL;

    const char *src = input;
    char *dst = escaped;
    while (*src) {
        switch (*src) {
            case '&': strcpy(dst, "&amp;"); dst += 5; break;
            case '<': strcpy(dst, "&lt;"); dst += 4; break;
            case '>': strcpy(dst, "&gt;"); dst += 4; break;
            case '"': strcpy(dst, "&quot;"); dst += 6; break;
            case '\'': strcpy(dst, "&#39;"); dst += 5; break;
            default: *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
    return escaped;
}

// Function to generate a greeting message
char* hello(const char* username) {
    if (username == NULL) return NULL;

    size_t len = strlen(username);
    char *message = malloc((len + 8) * sizeof(char));
    if (!message) return NULL;

    snprintf(message, len + 8, "Hello %s", username);
    char *escaped_message = escape(message);
    free(message);
    return escaped_message;
}

// Function to handle URL mapping
void handle_request(const char* url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        const char* username = url + 7;
        char *response = hello(username);
        if (response != NULL) {
            printf("%s\n", response);
            free(response);
        } else {
            printf("Error generating greeting message.\n");
        }
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Example usage
    handle_request("/hello/JohnDoe");
    handle_request("/hello/&<>'\"");

    return 0;
}