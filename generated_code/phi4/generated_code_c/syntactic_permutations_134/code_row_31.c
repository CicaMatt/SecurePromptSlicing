#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *url;
    int (*func)(const char *);
} URLFunctionMap;

#define MAX_URLS 10

char* escape(const char* input) {
    size_t len = strlen(input);
    char *escaped_str = malloc(len * 6 + 1); // Each character can become up to 5 characters long
    if (!escaped_str) return NULL;
    
    for (size_t i = 0; i < len; ++i) {
        switch (input[i]) {
            case '&':
                strcpy(escaped_str + (i * 6), "&amp;");
                break;
            case '<':
                strcpy(escaped_str + (i * 6), "&lt;");
                break;
            case '>':
                strcpy(escaped_str + (i * 6), "&gt;");
                break;
            case '"':
                strcpy(escaped_str + (i * 6), "&quot;");
                break;
            case '\'':
                strcpy(escaped_str + (i * 6), "&#x27;");
                break;
            default:
                escaped_str[i] = input[i];
                break;
        }
    }

    escaped_str[len * 6] = '\0';
    
    // Remove trailing null characters
    char* end = escaped_str + len * 6 - 1;
    while (end > escaped_str && *(end) == '\0') {
        *end-- = '\0';
    }
    
    return escaped_str;
}

int hello(const char* username) {
    const char* greeting = "Hello ";
    int length = strlen(greeting) + strlen(username) + 1; // +1 for null terminator
    char* message = malloc(length);
    if (!message) return -1;

    strcpy(message, greeting);
    strcat(message, escape(username));

    printf("%s\n", message);

    free(message);
    return 0;
}

int map_function(const char *url) {
    URLFunctionMap url_map[MAX_URLS] = {
        {"/hello", hello},
        // Add more mappings as needed
    };

    for (int i = 0; i < MAX_URLS; ++i) {
        if (strcmp(url, url_map[i].url) == 0) {
            return url_map[i].func(NULL);
        }
    }

    printf("No function mapped to URL: %s\n", url);
    return -1;
}

int main() {
    map_function("/hello");
    // Add more test cases as needed
    return 0;
}