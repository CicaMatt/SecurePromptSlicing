#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *str) {
    int i, j;
    int len = strlen(str);
    char *escaped_str = malloc(len * 6 + 1); // Each char can become up to 6 chars in the worst case
    for (i = 0, j = 0; str[i]; i++) {
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
                strcpy(&escaped_str[j], "&#39;");
                j += 5;
                break;
            default:
                escaped_str[j++] = str[i];
        }
    }
    escaped_str[j] = '\0';
    return escaped_str;
}

char* hello(const char *username) {
    int len = strlen(username);
    char *message = malloc(7 + len + 1); // "Hello " and space for username and null terminator
    strcpy(message, "Hello ");
    strcat(message, escape(username));
    return message;
}

int main() {
    const char *url = "/hello/username";
    const char *username = "user&name";
    
    if (strcmp(url, "/hello/") == 0) { // This is a simplified check
        printf("URL path should include username\n");
        return 1;
    }
    
    // Extracting username from URL for demonstration purposes
    username = url + strlen("/hello/");
    
    char *greeting = hello(username);
    printf("%s\n", greeting);
    free(greeting); // Free the allocated memory for the greeting message
    
    return 0;
}