#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *str) {
    int len = strlen(str);
    char *escaped_str = malloc(len * 6 + 1); // Each character could be replaced by up to 6 characters
    int j = 0;
    for (int i = 0; i < len; i++) {
        switch (str[i]) {
            case '&': 
                strcpy(&escaped_str[j], "&amp;");
                j += 5;
                break;
            case '<': 
                strcpy(&escaped_str[j], "&lt;");
                j += 4;
                break;
            case '>': 
                strcpy(&escaped_str[j], "&gt;");
                j += 4;
                break;
            case '"': 
                strcpy(&escaped_str[j], "&quot;");
                j += 6;
                break;
            case '\'': 
                strcpy(&escaped_str[j], "&#x27;");
                j += 6;
                break;
            default:
                escaped_str[j++] = str[i];
        }
    }
    escaped_str[j] = '\0';
    return escaped_str;
}

char* hello(const char *username) {
    char *safe_username = escape(username);
    char *greeting = malloc(strlen(safe_username) + 7); // "Hello " + safe_username + "\0"
    sprintf(greeting, "Hello %s", safe_username);
    free(safe_username);
    return greeting;
}

void route_hello(const char *url) {
    const char prefix[] = "/hello/";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        char *username = strdup(url + strlen(prefix));
        char *message = hello(username);
        printf("%s\n", message);
        free(message);
        free(username);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *url = "/hello/John&Doe";
    route_hello(url);
    return 0;
}