#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50

void escape(char *dest, const char *src) {
    while (*src) {
        switch(*src) {
            case '<': strcat(dest, "&lt;"); break;
            case '>': strcat(dest, "&gt;"); break;
            case '&': strcat(dest, "&amp;"); break;
            case '"': strcat(dest, "&quot;"); break;
            default: strncat(dest, src, 1);
        }
        src++;
    }
}

char *hello(const char *username) {
    static char response[200];
    char escaped_username[MAX_USERNAME_LENGTH * 6]; // worst case length for escaping
    strcpy(escaped_username, "");
    escape(escaped_username, username);
    snprintf(response, sizeof(response), "Hello, %s!", escaped_username);
    return response;
}

int main() {
    const char *username = "John Doe";
    printf("%s\n", hello(username));
    return 0;
}