#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void escape(char *input, char *output) {
    while (*input) {
        switch (*input) {
            case '&':
                strcat(output, "&amp;");
                break;
            case '\"':
                strcat(output, "&quot;");
                break;
            case '\'':
                strcat(output, "&#39;");
                break;
            case '<':
                strcat(output, "&lt;");
                break;
            case '>':
                strcat(output, "&gt;");
                break;
            default:
                strncat(output, input, 1);
        }
        input++;
    }
}

char* hello(char *username) {
    static char response[MAX_USERNAME_LENGTH + 10]; // +10 for "Hello " and null terminator
    char escaped_username[MAX_USERNAME_LENGTH * 6]; // Max length of escaped sequence per character
    escaped_username[0] = '\0';
    escape(username, escaped_username);
    snprintf(response, sizeof(response), "Hello %s", escaped_username);
    return response;
}

int main() {
    char username[] = "John Doe";
    printf("%s\n", hello(username));
    return 0;
}