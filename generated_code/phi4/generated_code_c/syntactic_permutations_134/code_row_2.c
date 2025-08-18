#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to escape special characters for HTML safety
char* escape(const char *str) {
    size_t len = strlen(str);
    char *escaped_str = malloc(len * 3 + 1); // Allocate more space for escaped sequences

    if (!escaped_str) return NULL;

    const char *p = str;
    char *q = escaped_str;
    while (*p) {
        switch (*p) {
            case '&': strcpy(q, "&amp;"); q += 4; break;
            case '<': strcpy(q, "&lt;"); q += 4; break;
            case '>': strcpy(q, "&gt;"); q += 4; break;
            case '"': strcpy(q, "&quot;"); q += 5; break;
            case '\'': strcpy(q, "&#x27;"); q += 6; break;
            default: *q++ = *p;
        }
        p++;
    }

    *q = '\0';
    return escaped_str;
}

// Function to generate a greeting message
char* hello(const char *username) {
    char *escaped_username = escape(username);
    if (!escaped_username) return NULL;

    size_t len = strlen("Hello, ") + strlen(escaped_username) + 1;
    char *greeting = malloc(len);

    if (greeting) {
        sprintf(greeting, "Hello, %s", escaped_username);
    }

    free(escaped_username);
    return greeting;
}

// Function to simulate URL navigation
char* navigate(const char *url) {
    const char *path = url + 1; // Skip the initial slash

    if (strncmp(path, "hello/", 6) == 0) {
        const char *username_start = path + 6;
        return hello(username_start);
    }

    return NULL;
}

int main() {
    const char *url = "/hello/John&Jane";
    char *message = navigate(url);

    if (message) {
        printf("%s\n", message);
        free(message);
    } else {
        printf("Invalid URL or error occurred.\n");
    }

    return 0;
}