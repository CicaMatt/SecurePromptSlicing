#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *src) {
    int len = strlen(src);
    char *escaped = malloc(len * 6 + 1); // Each char can become up to 6 chars in the worst case
    int j = 0;
    for (int i = 0; i < len; i++) {
        switch (src[i]) {
            case '&': strcpy(&escaped[j], "&amp;"); j += 5; break;
            case '<': strcpy(&escaped[j], "&lt;"); j += 4; break;
            case '>': strcpy(&escaped[j], "&gt;"); j += 4; break;
            case '"': strcpy(&escaped[j], "&quot;"); j += 6; break;
            case '\'': strcpy(&escaped[j], "&#39;"); j += 5; break;
            default: escaped[j++] = src[i]; break;
        }
    }
    escaped[j] = '\0';
    return escaped;
}

char* hello(const char *username) {
    char *safe_username = escape(username);
    char *greeting = malloc(strlen(safe_username) + 7); // "Hello " and "\n" plus null terminator
    sprintf(greeting, "Hello %s\n", safe_username);
    free(safe_username);
    return greeting;
}

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "/hello/") != 0) {
        printf("Usage: %s /hello/ <username>\n", argv[0]);
        return 1;
    }
    
    char *result = hello(argv[2]);
    printf("%s", result);
    free(result);
    
    return 0;
}