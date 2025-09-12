#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* escape(const char* input) {
    if (input == NULL) return NULL;
    
    size_t len = strlen(input);
    char *escaped = malloc(len * 6 + 1); // Each character might expand to 5 chars max
    if (!escaped) return NULL;

    for (size_t i = 0; i < len; ++i) {
        switch (input[i]) {
            case '&': strcat(escaped, "&amp;"); break;
            case '<': strcat(escaped, "&lt;"); break;
            case '>': strcat(escaped, "&gt;"); break;
            case '\"': strcat(escaped, "&quot;"); break;
            case '\'': strcat(escaped, "&#x27;"); break;
            default: {
                char buffer[2];
                buffer[0] = input[i];
                buffer[1] = '\0';
                strcat(escaped, buffer);
            } break;
        }
    }

    return escaped;
}

char* hello(const char* username) {
    if (username == NULL) return "Hello, guest!";
    
    char *escaped_username = escape(username);
    if (!escaped_username) return "Error escaping username.";
    
    // Allocate memory for the result string
    size_t len = strlen("Hello, ") + strlen(escaped_username) + 1;
    char *result = malloc(len);
    if (!result) {
        free(escaped_username);
        return "Memory allocation error.";
    }
    
    snprintf(result, len, "Hello, %s", escaped_username);
    free(escaped_username);
    
    return result;
}

void handle_request(const char* url) {
    const char *prefix = "/hello/";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        const char *username_start = url + strlen(prefix);
        char username[MAX_URL_LENGTH];
        strncpy(username, username_start, MAX_URL_LENGTH - 1);
        username[MAX_URL_LENGTH - 1] = '\0';

        char* response = hello(username);
        printf("%s\n", response);
        free(response);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Simulating a web server request
    const char *url = "/hello/John Doe";
    handle_request(url);

    return 0;
}