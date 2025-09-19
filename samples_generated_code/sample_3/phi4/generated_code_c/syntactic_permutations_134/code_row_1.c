#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
char* escape(const char* str);
char* hello(const char* username);

int main(int argc, char *argv[]) {
    if (argc != 2 || strcmp(argv[1], "/hello/") != 0) {
        printf("Usage: %s /hello/<username>\n", argv[0]);
        return 1;
    }

    // Extract the username from the argument
    const char* url = argv[1];
    const char* username_start = strstr(url, "/hello/");
    if (!username_start || strlen(username_start) <= strlen("/hello/")) {
        printf("Invalid URL format.\n");
        return 1;
    }

    const char* username = username_start + strlen("/hello/");
    char* response = hello(username);

    printf("%s\n", response);
    free(response);
    return 0;
}

// Function to escape special characters
char* escape(const char* str) {
    size_t len = strlen(str);
    char* escaped_str = malloc(len * 6 + 1); // Each character can be up to 5 chars long in HTML entities

    if (!escaped_str) return NULL;

    const char *src = str;
    char *dst = escaped_str;
    while (*src) {
        switch (*src) {
            case '&': strcpy(dst, "&amp;"); dst += 5; break;
            case '<': strcpy(dst, "&lt;"); dst += 4; break;
            case '>': strcpy(dst, "&gt;"); dst += 4; break;
            case '"': strcpy(dst, "&quot;"); dst += 6; break;
            case '\'': strcpy(dst, "&#x27;"); dst += 5; break;
            default: *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
    return escaped_str;
}

// Function to create a greeting message
char* hello(const char* username) {
    size_t len = strlen(username);
    char* escaped_username = escape(username);

    if (!escaped_username) return NULL;

    char* response = malloc(len + 13); // "Hello " + user length + null terminator

    if (!response) {
        free(escaped_username);
        return NULL;
    }

    sprintf(response, "Hello %s", escaped_username);
    free(escaped_username);

    return response;
}