#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* escape(const char *str) {
    int i, j;
    size_t len = strlen(str);
    char *escaped_str = malloc(len * 6 + 1); // Each character can be up to 6 characters in HTML-safe sequence

    for (i = 0, j = 0; str[i]; i++) {
        switch (str[i]) {
            case '<': strcpy(&escaped_str[j], "&lt;"); j += 4; break;
            case '>': strcpy(&escaped_str[j], "&gt;"); j += 4; break;
            case '&': strcpy(&escaped_str[j], "&amp;"); j += 5; break;
            case '\'': strcpy(&escaped_str[j], "&#39;"); j += 5; break;
            case '\"': strcpy(&escaped_str[j], "&quot;"); j += 6; break;
            default: escaped_str[j++] = str[i];
        }
    }
    escaped_str[j] = '\0';
    return escaped_str;
}

char* hello(const char *username) {
    char *safe_username = escape(username);
    char *greeting = malloc(strlen(safe_username) + 7); // "Hello " + "\n" + null terminator
    sprintf(greeting, "Hello %s\n", safe_username);
    free(safe_username);
    return greeting;
}

int main() {
    const char *username = "John&Doe";
    char *result = hello(username);
    printf("%s", result);
    free(result);
    return 0;
}