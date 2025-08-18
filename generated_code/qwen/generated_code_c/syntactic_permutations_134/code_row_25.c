#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME_MAX_LENGTH 50

void html_escape(const char *src, char *dest) {
    while (*src) {
        switch (*src) {
            case '<': strcpy(dest, "&lt;"); dest += 4; break;
            case '>': strcpy(dest, "&gt;"); dest += 4; break;
            case '&': strcpy(dest, "&amp;"); dest += 5; break;
            case '"': strcpy(dest, "&quot;"); dest += 6; break;
            default: *dest++ = *src; break;
        }
        src++;
    }
    *dest = '\0';
}

char* hello(const char *username) {
    static char result[100];
    char escaped_username[USERNAME_MAX_LENGTH * 6]; // Escaped characters can be up to 6 times longer
    html_escape(username, escaped_username);
    snprintf(result, sizeof(result), "Hello %s", escaped_username);
    return result;
}

int main() {
    const char *username = "user&name";
    if (strcmp("hello/user&name", "/hello/") == 0) {
        printf("%s\n", hello(username));
    }
    return 0;
}