#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
char* escape(const char* str);
void handle_request(const char* url);

// Define the maximum length for strings
#define MAX_URL_LENGTH 256
#define MAX_USERNAME_LENGTH 50

// Mapping from URL to function pointer
typedef void (*request_handler)(const char*);

typedef struct {
    const char* pattern;
    request_handler handler;
} route;

// Function implementations
char* escape(const char* str) {
    static char escaped_str[MAX_URL_LENGTH];
    size_t i, j = 0;
    
    for (i = 0; str[i] != '\0' && j < MAX_URL_LENGTH - 1; ++i) {
        switch (str[i]) {
            case '<': strcpy(&escaped_str[j], "&lt;"); j += 4; break;
            case '>': strcpy(&escaped_str[j], "&gt;"); j += 4; break;
            case '&': strcpy(&escaped_str[j], "&amp;"); j += 5; break;
            case '"': strcpy(&escaped_str[j], "&quot;"); j += 6; break;
            default: escaped_str[j++] = str[i];
        }
    }
    
    escaped_str[j] = '\0';
    return escaped_str;
}

void hello(const char* username) {
    printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n");
    printf("Hello %s", escape(username));
}

// Decorator function to map URL to the correct handler
void handle_request(const char* url) {
    route routes[] = {
        {"/hello/", hello},
        {NULL, NULL}
    };

    for (int i = 0; routes[i].pattern != NULL; ++i) {
        size_t pattern_len = strlen(routes[i].pattern);
        if (strncmp(url, routes[i].pattern, pattern_len) == 0 && url[pattern_len] == '/') {
            const char* username = url + pattern_len + 1;
            if (*username != '\0') {
                routes[i].handler(username);
                return;
            }
        }
    }

    printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\n");
    printf("Not Found");
}

int main() {
    char url[MAX_URL_LENGTH];

    // Simulating user input for URL
    printf("Enter the full URL to navigate: ");
    if (fgets(url, MAX_URL_LENGTH, stdin) != NULL) {
        size_t len = strlen(url);
        if (url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }
        
        handle_request(url);
    }

    return 0;
}