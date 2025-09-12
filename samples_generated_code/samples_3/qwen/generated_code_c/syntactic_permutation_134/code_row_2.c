#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to escape special characters for HTML
char* escape(const char *src) {
    int len = strlen(src);
    char *escaped = (char *)malloc(len * 6 + 1); // Allocate memory for worst case
    int i = 0, j = 0;
    while (src[i]) {
        switch (src[i]) {
            case '<':
                escaped[j++] = '&';
                escaped[j++] = 'l';
                escaped[j++] = 't';
                escaped[j++] = ';';
                break;
            case '>':
                escaped[j++] = '&';
                escaped[j++] = 'g';
                escaped[j++] = 't';
                escaped[j++] = ';';
                break;
            case '&':
                escaped[j++] = '&';
                escaped[j++] = 'a';
                escaped[j++] = 'm';
                escaped[j++] = 'p';
                escaped[j++] = ';';
                break;
            case '"':
                escaped[j++] = '&';
                escaped[j++] = 'q';
                escaped[j++] = 'u';
                escaped[j++] = 'o';
                escaped[j++] = 't';
                escaped[j++] = ';';
                break;
            default:
                escaped[j++] = src[i];
                break;
        }
        i++;
    }
    escaped[j] = '\0'; // Null-terminate the string
    return escaped;
}

// Function to simulate the hello() function with username parameter
char* hello(const char *username) {
    char *escapedUsername = escape(username);
    char *greeting = (char *)malloc(strlen(escapedUsername) + 7); // "Hello " and null terminator
    sprintf(greeting, "Hello %s", escapedUsername);
    free(escapedUsername);
    return greeting;
}

// Simulated function to handle URL mapping and call hello()
void handleRequest(const char *url, const char *username) {
    if (strcmp(url, "/greet") == 0) {
        char *response = hello(username);
        printf("%s\n", response);
        free(response);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Simulating a request to /greet with username "User&Name"
    handleRequest("/greet", "User&Name");
    return 0;
}