#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char* input) {
    int length = strlen(input);
    int new_length = 0;
    for (int i = 0; i < length; i++) {
        switch (input[i]) {
            case '&': new_length += 5; break;
            case '<': new_length += 4; break;
            case '>': new_length += 4; break;
            case '"': new_length += 6; break;
            case '\'': new_length += 6; break;
            default: new_length++; break;
        }
    }

    char* escaped = (char*)malloc(new_length + 1);
    if (!escaped) return NULL;

    int j = 0;
    for (int i = 0; i < length; i++) {
        switch (input[i]) {
            case '&': strcpy(escaped + j, "&amp;"); j += 5; break;
            case '<': strcpy(escaped + j, "&lt;"); j += 4; break;
            case '>': strcpy(escaped + j, "&gt;"); j += 4; break;
            case '"': strcpy(escaped + j, "&quot;"); j += 6; break;
            case '\'': strcpy(escaped + j, "&#x27;"); j += 6; break;
            default: escaped[j++] = input[i]; break;
        }
    }
    escaped[new_length] = '\0';

    return escaped;
}

char* hello(const char* username) {
    char* safe_username = escape(username);
    if (!safe_username) return NULL;

    char* greeting = (char*)malloc(strlen(safe_username) + 7);
    if (!greeting) {
        free(safe_username);
        return NULL;
    }

    sprintf(greeting, "Hello %s", safe_username);

    free(safe_username);
    return greeting;
}

int main() {
    const char* username = "user&name";
    char* result = hello(username);
    if (result) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}