#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* escape(const char *input) {
    int length = strlen(input);
    char *output = malloc(length * 6 + 1); // Each character can become up to 6 characters long
    int outputIndex = 0;
    
    for (int i = 0; i < length; i++) {
        switch (input[i]) {
            case '&': strcpy(output + outputIndex, "&amp;"); outputIndex += 5; break;
            case '<': strcpy(output + outputIndex, "&lt;"); outputIndex += 4; break;
            case '>': strcpy(output + outputIndex, "&gt;"); outputIndex += 4; break;
            case '"': strcpy(output + outputIndex, "&quot;"); outputIndex += 6; break;
            case '\'': strcpy(output + outputIndex, "&#39;"); outputIndex += 5; break;
            default: output[outputIndex++] = input[i]; break;
        }
    }
    output[outputIndex] = '\0';
    return output;
}

char* hello(const char *username) {
    char *escapedUsername = escape(username);
    char *greeting = malloc(strlen(escapedUsername) + 8); // "Hello " and "\n" plus null terminator
    sprintf(greeting, "Hello %s\n", escapedUsername);
    free(escapedUsername);
    return greeting;
}

void handleRequest(const char *url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        char username[256];
        strncpy(username, url + 7, sizeof(username));
        username[sizeof(username) - 1] = '\0'; // Ensure null termination
        char *response = hello(username);
        printf("%s", response);
        free(response);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    handleRequest("/hello/John&Doe");
    return 0;
}