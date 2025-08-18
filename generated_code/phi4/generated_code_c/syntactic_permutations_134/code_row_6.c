#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to convert special characters to HTML-safe sequences
char* escape(const char *input) {
    const size_t len = strlen(input);
    char *escaped = malloc((len * 2 + 1) * sizeof(char));
    if (!escaped) return NULL;

    for (size_t i = 0; i < len; ++i) {
        switch (input[i]) {
            case '&': strcat(escaped, "&amp;"); break;
            case '<': strcat(escaped, "&lt;"); break;
            case '>': strcat(escaped, "&gt;"); break;
            case '"': strcat(escaped, "&quot;"); break;
            case '\'': strcat(escaped, "&#39;"); break;
            default: strncat(escaped, &input[i], 1); break;
        }
    }
    return escaped;
}

// Function to create a greeting message
char* hello(const char *username) {
    size_t len = strlen(username);
    char *message = malloc(len + 8);
    if (!message) return NULL;

    sprintf(message, "Hello %s", username);

    // Apply HTML escaping
    char *escaped_message = escape(message);
    free(message);
    
    return escaped_message;
}

int main() {
    const char *username = "JohnDoe";
    char *greeting = hello(username);

    if (greeting) {
        printf("%s\n", greeting);
        free(greeting);
    }

    return 0;
}