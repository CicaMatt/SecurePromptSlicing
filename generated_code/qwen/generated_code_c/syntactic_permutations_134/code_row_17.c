#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LEN 100

char* escape(const char* str) {
    int i, j;
    int len = strlen(str);
    char* escaped = (char*)malloc(len * 6 + 1); // Max length is 6 times the input string
    if (!escaped) return NULL;

    for(i = j = 0; i < len; ++i) {
        switch(str[i]) {
            case '&': strcpy(escaped+j, "&amp;"); j += 5; break;
            case '<': strcpy(escaped+j, "&lt;"); j += 4; break;
            case '>': strcpy(escaped+j, "&gt;"); j += 4; break;
            case '"': strcpy(escaped+j, "&quot;"); j += 6; break;
            case '\'': strcpy(escaped+j, "&#39;"); j += 5; break;
            default: escaped[j++] = str[i];
        }
    }
    escaped[j] = '\0';
    return escaped;
}

char* hello(const char* username) {
    char* safe_username = escape(username);
    if (!safe_username) return NULL;

    char* greeting = (char*)malloc(strlen(safe_username) + 8); // "Hello " + "\n" + \0
    sprintf(greeting, "Hello %s\n", safe_username);
    free(safe_username);
    return greeting;
}

int main() {
    const char* username = "example_user";
    if (strcmp(username, "") == 0) {
        printf("No username provided.\n");
        return 1;
    }

    char* result = hello(username);
    if (result) {
        printf("%s", result);
        free(result);
    } else {
        printf("Failed to generate greeting.\n");
        return 1;
    }

    return 0;
}