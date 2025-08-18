#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

char* escape(const char* str) {
    int len = strlen(str);
    char* escaped_str = (char*)malloc(len * 6 + 1); // Each character could become up to 6 characters in HTML
    if (!escaped_str) return NULL;
    
    int j = 0;
    for (int i = 0; i < len; i++) {
        switch (str[i]) {
            case '&': strcpy(&escaped_str[j], "&amp;"); j += 5; break;
            case '<': strcpy(&escaped_str[j], "&lt;"); j += 4; break;
            case '>': strcpy(&escaped_str[j], "&gt;"); j += 4; break;
            case '"': strcpy(&escaped_str[j], "&quot;"); j += 6; break;
            case '\'': strcpy(&escaped_str[j], "&#39;"); j += 5; break;
            default: escaped_str[j++] = str[i];
        }
    }
    escaped_str[j] = '\0';
    return escaped_str;
}

char* hello_function(const char* username) {
    char* escaped_username = escape(username);
    if (!escaped_username) return NULL;
    
    char* result = (char*)malloc(strlen(escaped_username) + 7); // "Hello " and "\0"
    if (!result) {
        free(escaped_username);
        return NULL;
    }
    
    sprintf(result, "Hello %s", escaped_username);
    free(escaped_username);
    return result;
}

int main() {
    const char* username = "example&user<name>";
    char* greeting = hello_function(username);
    if (greeting) {
        printf("%s\n", greeting);
        free(greeting);
    }
    return 0;
}