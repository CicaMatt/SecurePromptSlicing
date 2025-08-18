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
            default: *output++ = *input;
        }
        input++;
    }
    *output = '\0';
}

void hello(char *username) {
    char safe_username[MAX_USERNAME_LENGTH * 6]; // Worst case expansion
    escape(username, safe_username);
    printf("Hello %s\n", safe_username);
}

int main() {
    char username[] = "John Doe";
    hello(username);
    return 0;
}