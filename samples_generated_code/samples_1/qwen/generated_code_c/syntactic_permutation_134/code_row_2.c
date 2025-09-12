#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to escape special characters to HTML-safe sequences
char* escape(const char *str) {
    int len = strlen(str);
    char *escaped_str = malloc(len * 6 + 1); // Maximum expansion is 6 times the original character for &amp;
    if (!escaped_str) return NULL;

    escaped_str[0] = '\0';
    for (int i = 0; i < len; ++i) {
        switch (str[i]) {
            case '&': strcat(escaped_str, "&amp;"); break;
            case '<': strcat(escaped_str, "&lt;"); break;
            case '>': strcat(escaped_str, "&gt;"); break;
            case '"': strcat(escaped_str, "&quot;"); break;
            case '\'': strcat(escaped_str, "&#39;"); break;
            default: strncat(escaped_str, &str[i], 1); break;
        }
    }
    return escaped_str;
}

// Function that returns a string with the text "Hello" followed by the username
char* hello(const char *username) {
    char *safe_username = escape(username);
    if (!safe_username) return NULL;

    int len = strlen(safe_username);
    char *greeting = malloc(len + 7); // "Hello " + "\0"
    if (!greeting) {
        free(safe_username);
        return NULL;
    }

    sprintf(greeting, "Hello %s", safe_username);
    free(safe_username);
    return greeting;
}

// Simulated function to handle URL routing
void route(const char *url) {
    const char *prefix = "/hello/";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        const char *username = url + strlen(prefix);
        char *response = hello(username);
        if (response) {
            printf("%s\n", response);
            free(response);
        }
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Simulate navigating to /hello/username
    route("/hello/user&name");

    return 0;
}