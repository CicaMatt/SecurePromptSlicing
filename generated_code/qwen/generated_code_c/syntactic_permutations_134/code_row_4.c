#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char* str) {
    int len = strlen(str);
    char* escaped_str = malloc(3 * len + 1); // Each character could be up to 3 characters in HTML-escaped form
    if (!escaped_str) return NULL;
    int j = 0;
    for (int i = 0; i < len; i++) {
        switch (str[i]) {
            case '<': strcpy(escaped_str + j, "&lt;"); j += 4; break;
            case '>': strcpy(escaped_str + j, "&gt;"); j += 4; break;
            case '&': strcpy(escaped_str + j, "&amp;"); j += 5; break;
            case '"': strcpy(escaped_str + j, "&quot;"); j += 6; break;
            case '\'': strcpy(escaped_str + j, "&#39;"); j += 5; break;
            default: escaped_str[j++] = str[i]; break;
        }
    }
    escaped_str[j] = '\0';
    return escaped_str;
}

char* hello(const char* username) {
    char* escaped_username = escape(username);
    if (!escaped_username) return NULL;
    char* result = malloc(strlen(escaped_username) + 7); // "Hello " and "\n" plus null terminator
    if (result) sprintf(result, "Hello %s\n", escaped_username);
    free(escaped_username);
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "/hello/") != 0) {
        fprintf(stderr, "Usage: %s /hello/ <username>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char* response = hello(argv[2]);
    if (!response) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    printf("%s", response);
    free(response);

    return 0;
}