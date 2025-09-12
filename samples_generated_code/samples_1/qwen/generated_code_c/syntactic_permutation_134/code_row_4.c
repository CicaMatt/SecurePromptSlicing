#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char* str) {
    int len = strlen(str);
    char* result = (char*)malloc(len * 6 + 1); // Each character could expand to 6 characters in the worst case
    int i, j;
    for (i = 0, j = 0; i < len; i++) {
        switch (str[i]) {
            case '&': strcpy(&result[j], "&amp;"); j += 5; break;
            case '<': strcpy(&result[j], "&lt;"); j += 4; break;
            case '>': strcpy(&result[j], "&gt;"); j += 4; break;
            case '"': strcpy(&result[j], "&quot;"); j += 6; break;
            case '\'': strcpy(&result[j], "&#39;"); j += 5; break;
            default: result[j++] = str[i];
        }
    }
    result[j] = '\0';
    return result;
}

char* hello(const char* username) {
    char* escaped_username = escape(username);
    char* response = (char*)malloc(strlen(escaped_username) + 13); // "Hello, " and trailing null
    sprintf(response, "Hello, %s", escaped_username);
    free(escaped_username);
    return response;
}

int main() {
    const char* username = "user&name";
    char* result = hello(username);
    printf("%s\n", result);
    free(result);
    return 0;
}