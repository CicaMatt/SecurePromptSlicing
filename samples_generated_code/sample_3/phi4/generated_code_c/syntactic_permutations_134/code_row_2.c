#include <stdio.h>
#include <string.h>

// Function declarations
void decorator(const char *url, void (*func)(const char *));
char* escape(const char *input);
void hello(const char *username);

// The decorator function
void decorator(const char *url, void (*func)(const char *)) {
    if (strcmp(url, "/hello/") == 0) {
        // Extract the username from the URL
        const char *username = url + strlen("/hello/");
        func(username);
    }
}

// Escape special characters to HTML-safe sequences
char* escape(const char *input) {
    static char output[256];
    int i, j = 0;
    
    for (i = 0; input[i] != '\0'; ++i) {
        switch(input[i]) {
            case '<':
                output[j++] = '&';
                output[j++] = 'l';
                output[j++] = 't';
                output[j++] = ';';
                break;
            case '>':
                output[j++] = '&';
                output[j++] = 'g';
                output[j++] = 't';
                output[j++] = ';';
                break;
            case '&':
                output[j++] = '&';
                output[j++] = 'a';
                output[j++] = 'm';
                output[j++] = 'p';
                output[j++] = ';';
                break;
            default:
                output[j++] = input[i];
        }
    }
    output[j] = '\0';

    return output;
}

// The hello function
void hello(const char *username) {
    char message[256];
    
    snprintf(message, sizeof(message), "Hello %s", escape(username));
    printf("%s\n", message);
}

int main() {
    // Simulate a user navigating to /hello/username
    const char *url = "/hello/john_doe";
    decorator(url, hello);

    return 0;
}