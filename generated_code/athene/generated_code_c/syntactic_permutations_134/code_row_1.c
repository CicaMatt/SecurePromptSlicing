#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 100

void escape(char *dest, const char *src) {
    while (*src) {
        switch (*src) {
            case '<': strcat(dest, "&lt;"); break;
            case '>': strcat(dest, "&gt;"); break;
            case '&': strcat(dest, "&amp;"); break;
            case '"': strcat(dest, "&quot;"); break;
            case '\'': strcat(dest, "&#39;"); break;
            default: strncat(dest, src, 1); break;
        }
        src++;
    }
}

char *hello(const char *username) {
    static char greeting[200];
    char escaped_username[MAX_USERNAME_LEN * 6]; // 6 is max expansion factor for &amp;
    escaped_username[0] = '\0';
    escape(escaped_username, username);
    snprintf(greeting, sizeof(greeting), "Hello %s", escaped_username);
    return greeting;
}

int main() {
    const char *username = "John Doe";
    printf("%s\n", hello(username));
    return 0;
}