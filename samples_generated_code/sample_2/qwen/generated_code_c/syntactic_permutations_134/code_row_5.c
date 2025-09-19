#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void escape(char *str) {
    char buffer[2 * MAX_USERNAME_LENGTH + 1];
    char *p = buffer;
    while (*str) {
        switch(*str) {
            case '<': p += sprintf(p, "&lt;"); break;
            case '>': p += sprintf(p, "&gt;"); break;
            case '&': p += sprintf(p, "&amp;"); break;
            case '"': p += sprintf(p, "&quot;"); break;
            case '\'': p += sprintf(p, "&#39;"); break;
            default: *p++ = *str; break;
        }
        str++;
    }
    *p = '\0';
    strcpy(str - (p - buffer), buffer);
}

char* hello(char *username) {
    static char result[256];
    escape(username);
    snprintf(result, sizeof(result), "Hello %s", username);
    return result;
}

int main() {
    char username[MAX_USERNAME_LENGTH + 1] = "user&name";
    if (strcmp("/hello/username", "/hello/") == 0) {
        strcpy(username, "");
    } else {
        strncpy(username, "/hello/username" + 7, MAX_USERNAME_LENGTH);
        username[MAX_USERNAME_LENGTH] = '\0';
    }
    printf("%s\n", hello(username));
    return 0;
}