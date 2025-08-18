#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *str) {
    int len = strlen(str);
    char *escaped = (char *)malloc(len * 6 + 1); // Each character can expand to up to 6 characters in the worst case
    int j = 0;
    for (int i = 0; str[i]; ++i) {
        switch (str[i]) {
            case '<':
                escaped[j++] = '&';
                escaped[j++] = 'l';
                escaped[j++] = 't';
                escaped[j++] = ';';
                break;
            case '>':
                escaped[j++] = '&';
                escaped[j++] = 'g';
                escaped[j++] = 't';
                escaped[j++] = ';';
                break;
            case '&':
                escaped[j++] = '&';
                escaped[j++] = 'a';
                escaped[j++] = 'm';
                escaped[j++] = 'p';
                escaped[j++] = ';';
                break;
            case '"':
                escaped[j++] = '&';
                escaped[j++] = 'q';
                escaped[j++] = 'u';
                escaped[j++] = 'o';
                escaped[j++] = 't';
                escaped[j++] = ';';
                break;
            case '\'':
                escaped[j++] = '&';
                escaped[j++] = '#';
                escaped[j++] = '3';
                escaped[j++] = '9';
                escaped[j++] = ';';
                break;
            default:
                escaped[j++] = str[i];
        }
    }
    escaped[j] = '\0';
    return escaped;
}

char* hello(const char *username) {
    char *safe_username = escape(username);
    char *result = (char *)malloc(strlen(safe_username) + 7); // "Hello " + safe_username + "\n"
    sprintf(result, "Hello %s\n", safe_username);
    free(safe_username);
    return result;
}

int main() {
    const char *username = "example_user";
    if (strcmp("/hello/example_user", "/hello/username") == 0) { // Simulating URL match
        char *greeting = hello(username);
        printf("%s", greeting);
        free(greeting);
    }
    return 0;
}