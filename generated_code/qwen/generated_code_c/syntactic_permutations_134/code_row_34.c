#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* escape(const char *str) {
    int i, j;
    const char *special_chars = "&\"'><";
    size_t len = strlen(str);
    char *result = malloc(len * 5 + 1); // worst case scenario

    for (i = 0, j = 0; str[i]; ++i) {
        if (strchr(special_chars, str[i])) {
            switch (str[i]) {
                case '&': strcpy(&result[j], "&amp;"); break;
                case '"': strcpy(&result[j], "&quot;"); break;
                case '\'': strcpy(&result[j], "&#39;"); break;
                case '>': strcpy(&result[j], "&gt;"); break;
                case '<': strcpy(&result[j], "&lt;"); break;
            }
            j += strlen(&result[j]);
        } else {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    return result;
}

char* hello(const char *username) {
    char *escaped_username = escape(username);
    char *greeting = malloc(strlen("Hello ") + strlen(escaped_username) + 1);
    strcpy(greeting, "Hello ");
    strcat(greeting, escaped_username);
    free(escaped_username);
    return greeting;
}

int main() {
    const char *username = "<script>alert('XSS')</script>";
    char *message = hello(username);
    printf("%s\n", message);
    free(message);
    return 0;
}