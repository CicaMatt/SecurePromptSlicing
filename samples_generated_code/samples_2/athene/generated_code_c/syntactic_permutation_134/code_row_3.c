#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 100

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

char* hello(char *username) {
    static char buffer[200];
    char escaped_username[MAX_USERNAME_LEN + 10]; // Extra space for escape sequences
    escape(username, escaped_username);
    snprintf(buffer, sizeof(buffer), "Hello %s", escaped_username);
    return buffer;
}

int main() {
    char username[] = "username";
    printf("%s\n", hello(username));
    return 0;
}