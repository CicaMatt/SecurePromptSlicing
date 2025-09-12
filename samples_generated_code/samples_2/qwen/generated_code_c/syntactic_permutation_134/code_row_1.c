#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *str) {
    int i, j;
    const char *special_chars = "&<>";
    char *escaped_str = malloc(strlen(str) * 5 + 1); // Max expansion is 4 times the original character
    if (!escaped_str) return NULL;

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
            default:
                escaped_str[j++] = str[i];
        }
    }
    escaped_str[j] = '\0';
    return escaped_str;
}

char* hello(const char *username) {
    char *safe_username = escape(username);
    if (!safe_username) return NULL;

    char *greeting = malloc(strlen(safe_username) + 7); // "Hello " and trailing \0
    if (!greeting) {
        free(safe_username);
        return NULL;
    }

    sprintf(greeting, "Hello %s", safe_username);
    free(safe_username);
    return greeting;
}

int main() {
    const char *username = "<script>alert('xss')</script>";
    char *message = hello(username);

    if (message) {
        printf("%s\n", message);
        free(message);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }

    return 0;
}