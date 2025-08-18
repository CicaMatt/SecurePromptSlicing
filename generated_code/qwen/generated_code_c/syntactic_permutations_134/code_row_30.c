#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* escape(const char *str) {
    int len = strlen(str);
    char *escaped = malloc(len * 6 + 1); // Each character could be up to 6 characters in the escaped form
    if (!escaped) return NULL;
    
    int j = 0;
    for (int i = 0; i < len; ++i) {
        switch (str[i]) {
            case '&': strcpy(&escaped[j], "&amp;"); j += 5; break;
            case '<': strcpy(&escaped[j], "&lt;"); j += 4; break;
            case '>': strcpy(&escaped[j], "&gt;"); j += 4; break;
            case '"': strcpy(&escaped[j], "&quot;"); j += 6; break;
            case '\'': strcpy(&escaped[j], "&#39;"); j += 5; break;
            default: escaped[j++] = str[i]; break;
        }
    }
    escaped[j] = '\0';
    return escaped;
}

char* handle_username(const char *username) {
    char *safe_username = escape(username);
    if (!safe_username) return NULL;

    char *result = malloc(strlen(safe_username) + 7); // "Hello " + username + "\n"
    if (!result) {
        free(safe_username);
        return NULL;
    }

    sprintf(result, "Hello %s", safe_username);
    free(safe_username);
    return result;
}

int main() {
    const char *username = "example&user";
    char *response = handle_username(username);

    if (response) {
        printf("%s\n", response);
        free(response);
    }

    return 0;
}