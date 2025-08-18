#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to convert special characters to HTML-safe sequences
char* escape(const char* input) {
    size_t length = strlen(input);
    char* output = (char*)malloc(3 * length + 1); // Allocate enough space for the worst-case scenario

    if (!output) return NULL;

    const char* html_entities[] = {"&", "<", ">", "\"", "\'"};
    const char* html_replacements[] = {"&amp;", "&lt;", "&gt;", "&quot;", "&#39;"};

    size_t output_index = 0;
    for (size_t i = 0; i < length; ++i) {
        int replaced = 0;
        for (int j = 0; j < 5; ++j) {
            if (input[i] == html_entities[j][0]) {
                strcpy(&output[output_index], html_replacements[j]);
                output_index += strlen(html_replacements[j]);
                replaced = 1;
                break;
            }
        }
        if (!replaced) {
            output[output_index++] = input[i];
        }
    }

    output[output_index] = '\0';
    return output;
}

// Decorator function
char* hello(const char* username) {
    char* greeting = (char*)malloc(strlen("Hello, ") + strlen(username) + 1);
    if (!greeting) return NULL;

    strcpy(greeting, "Hello, ");
    strcat(greeting, username);

    // Escape special characters in the greeting
    char* escaped_greeting = escape(greeting);
    free(greeting); // Free the original greeting to avoid memory leak

    return escaped_greeting;
}

// Simulating a web server handling a request to /hello/username
void handle_request(const char* path) {
    const char* prefix = "/hello/";
    if (strncmp(path, prefix, strlen(prefix)) == 0) {
        const char* username = path + strlen(prefix);
        char* response = hello(username);

        printf("%s\n", response); // Output the response
        free(response); // Free the allocated memory for the response
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    handle_request("/hello/John Doe");  // Example usage
    return 0;
}