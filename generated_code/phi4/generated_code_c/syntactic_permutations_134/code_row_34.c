#include <stdio.h>
#include <string.h>

// Function to convert special characters to HTML-safe sequences
void escape(const char* input, char* output) {
    while (*input) {
        switch (*input) {
            case '<':
                strcat(output, "&lt;");
                break;
            case '>':
                strcat(output, "&gt;");
                break;
            case '&':
                strcat(output, "&amp;");
                break;
            default:
                strncat(output, input, 1);
        }
        ++input;
    }
}

// Function to return a greeting message with the username
void hello(const char* username) {
    char message[256];
    snprintf(message, sizeof(message), "Hello %s", username);

    // Escape special characters in the message
    char escaped_message[512] = "";
    escape(message, escaped_message);

    printf("%s\n", escaped_message);
}

// Function that acts as a decorator to map URLs to functions
void route(const char* url) {
    if (strcmp(url, "/hello") == 0) {
        // Simulating receiving the username from request parameters or similar
        const char* username = "John Doe";
        hello(username);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Example URL to test the routing and function call
    route("/hello");

    return 0;
}