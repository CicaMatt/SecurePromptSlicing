#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void escape(char *input, char *output) {
    while (*input) {
        switch (*input) {
            case '<': strcpy(output, "&lt;"); output += 4; break;
            case '>': strcpy(output, "&gt;"); output += 4; break;
            case '&': strcpy(output, "&amp;"); output += 5; break;
            case '"': strcpy(output, "&quot;"); output += 6; break;
            default: *output++ = *input; break;
        }
        input++;
    }
    *output = '\0';
}

void hello(char *username) {
    char escaped_username[MAX_URL_LENGTH] = "";
    escape(username, escaped_username);
    printf("Hello %s\n", escaped_username);
}

int main() {
    char username[MAX_URL_LENGTH];
    strcpy(username, "John Doe"); // Example username
    hello(username);
    return 0;
}