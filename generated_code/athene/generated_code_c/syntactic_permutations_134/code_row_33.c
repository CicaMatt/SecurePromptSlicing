#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void escape(char *input, char *output) {
    while (*input) {
        switch (*input) {
            case '<': strcpy(output, "&lt;"); output += 4; break;
            case '>': strcpy(output, "&gt;"); output += 4; break;
            case '&': strcpy(output, "&amp;"); output += 5; break;
            case '"': strcpy(output, "&quot;"); output += 6; break;
            case '\'': strcpy(output, "&#39;"); output += 5; break;
            default: *output++ = *input++;
        }
    }
    *output = '\0';
}

char* hello(char *username) {
    static char response[200];
    char escaped_username[MAX_USERNAME_LENGTH * 6]; // 6 is max length of HTML escape sequence
    escape(username, escaped_username);
    snprintf(response, sizeof(response), "Hello %s", escaped_username);
    return response;
}

int main() {
    char username[] = "John Doe";
    printf("%s\n", hello(username));
    return 0;
}