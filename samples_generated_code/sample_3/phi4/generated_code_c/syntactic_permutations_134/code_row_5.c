#include <stdio.h>
#include <string.h>

// Function to escape special HTML characters
void escape(const char *input, char *output) {
    while (*input) {
        switch (*input) {
            case '&':
                strcat(output, "&amp;");
                break;
            case '<':
                strcat(output, "&lt;");
                break;
            case '>':
                strcat(output, "&gt;");
                break;
            case '"':
                strcat(output, "&quot;");
                break;
            case '\'':
                strcat(output, "&#x27;");
                break;
            default:
                strncat(output, input, 1);
        }
        input++;
    }
}

// Function to generate a greeting message
void hello(const char *username) {
    char safe_username[100];
    safe_username[0] = '\0'; // Initialize the output buffer

    escape(username, safe_username);

    printf("Hello %s\n", safe_username);
}

// Simulate handling of the URL and calling the appropriate function
void handle_request(const char *url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        const char *username = url + 7;
        hello(username);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Simulate user navigation to a URL
    handle_request("/hello/John&Jane");

    return 0;
}