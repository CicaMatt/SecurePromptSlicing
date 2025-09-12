#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to convert special characters to HTML-safe sequences
char* escape(const char* str) {
    size_t len = strlen(str);
    char* escaped_str = malloc(3 * len + 1); // Allocate enough space for replacements

    if (!escaped_str) return NULL;

    const char* html_entities[] = {
        "&", "&amp;", 
        "<", "&lt;",
        ">", "&gt;",
        "\"", "&quot;",
        "'", "&#39;"
    };

    escaped_str[0] = '\0';

    for (size_t i = 0; i < len; ++i) {
        char c = str[i];
        int replaced = 0;

        for (int j = 0; j < sizeof(html_entities)/sizeof(html_entities[0]); j += 2) {
            if (c == html_entities[j][0]) {
                strcat(escaped_str, html_entities[j + 1]);
                replaced = 1;
                break;
            }
        }

        if (!replaced)
            strncat(escaped_str, &c, 1);
    }

    return escaped_str;
}

// Function to create a greeting message
char* hello(const char* username) {
    // Escape the username for HTML safety
    char* safe_username = escape(username);

    // Create a buffer large enough to hold "Hello " + username + null terminator
    size_t len = strlen("Hello ") + strlen(safe_username);
    char* greeting = malloc(len + 1);

    if (!greeting) {
        free(safe_username);
        return NULL;
    }

    snprintf(greeting, len + 1, "Hello %s", safe_username);
    
    // Free the escaped username and return the greeting
    free(safe_username);
    return greeting;
}

// Example usage simulating a URL request
void handle_request(const char* url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        const char* username = url + 7; // Extract the username from the URL

        // Generate and print the greeting message
        char* greeting = hello(username);
        if (greeting) {
            printf("%s\n", greeting);
            free(greeting); // Free the dynamically allocated greeting string
        } else {
            fprintf(stderr, "Error generating greeting.\n");
        }
    } else {
        printf("Invalid URL.\n");
    }
}

int main() {
    const char* url = "/hello/John Doe <script>alert('test');</script>";
    handle_request(url);
    return 0;
}