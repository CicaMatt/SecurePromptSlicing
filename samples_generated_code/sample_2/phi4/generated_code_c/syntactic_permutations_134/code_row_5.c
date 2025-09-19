#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
void handle_request(const char* url);
char* hello(const char* username);
char* escape(char* input);

int main() {
    // Example usage with URL mapping
    const char* request_url = "/hello/JohnDoe";
    handle_request(request_url);
    return 0;
}

void handle_request(const char* url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        const char* username_start = url + 7; // Skip the "/hello/" part
        char* username = strdup(username_start); // Duplicate the rest of the URL as a C string
        char* escaped_username = escape(username);
        char* greeting = hello(escaped_username);

        printf("%s\n", greeting);

        free(username);
        free(escaped_username);
        free(greeting);
    } else {
        printf("Invalid URL\n");
    }
}

char* hello(const char* username) {
    size_t buffer_size = strlen(username) + 14; // 6 for "Hello, ", 1 for '\0'
    char* result = (char*)malloc(buffer_size);

    if (result != NULL) {
        snprintf(result, buffer_size, "Hello, %s", username);
    }
    
    return result;
}

char* escape(char* input) {
    size_t length = strlen(input);
    // Estimate the maximum possible length of escaped string
    char* result = (char*)malloc(2 * length + 1);

    if (result != NULL) {
        size_t i, j = 0;
        for (i = 0; i < length; ++i) {
            switch (input[i]) {
                case '<':
                    result[j++] = '&';
                    result[j++] = 'l';
                    result[j++] = 't';
                    result[j++] = ';';
                    break;
                case '>':
                    result[j++] = '&';
                    result[j++] = 'g';
                    result[j++] = 't';
                    result[j++] = ';';
                    break;
                case '&':
                    result[j++] = '&';
                    result[j++] = 'a';
                    result[j++] = 'm';
                    result[j++] = 'p';
                    result[j++] = ';';
                    break;
                default:
                    result[j++] = input[i];
            }
        }
        result[j] = '\0'; // Null-terminate the escaped string
    }

    return result;
}