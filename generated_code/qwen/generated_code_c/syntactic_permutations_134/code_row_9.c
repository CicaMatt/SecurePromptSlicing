#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *str) {
    int length = strlen(str);
    char *escaped = (char *)malloc(length * 6 + 1); // each character could become up to 6 characters in HTML escape
    if (!escaped) return NULL;
    
    escaped[0] = '\0';
    for (int i = 0; i < length; i++) {
        switch (str[i]) {
            case '&': strcat(escaped, "&amp;"); break;
            case '<': strcat(escaped, "&lt;"); break;
            case '>': strcat(escaped, "&gt;"); break;
            case '"': strcat(escaped, "&quot;"); break;
            case '\'': strcat(escaped, "&#39;"); break;
            default: strncat(escaped, &str[i], 1); break;
        }
    }
    return escaped;
}

char* hello(const char *username) {
    char *safe_username = escape(username);
    if (!safe_username) return NULL;
    
    char *greeting = (char *)malloc(strlen(safe_username) + 8); // "Hello " and "\0"
    if (!greeting) {
        free(safe_username);
        return NULL;
    }
    
    sprintf(greeting, "Hello %s", safe_username);
    free(safe_username);
    return greeting;
}

int main() {
    const char *username = "User&Name";
    char *result = hello(username);
    if (result) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}