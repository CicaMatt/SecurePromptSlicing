#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50

void escape(char *dest, const char *src) {
    while (*src) {
        switch(*src) {
            case '<': 
                strcpy(dest, "&lt;");
                dest += 4;
                break;
            case '>': 
                strcpy(dest, "&gt;");
                dest += 4;
                break;
            case '&': 
                strcpy(dest, "&amp;");
                dest += 5;
                break;
            case '"': 
                strcpy(dest, "&quot;");
                dest += 6;
                break;
            default: 
                *dest++ = *src;
        }
        src++;
    }
    *dest = '\0';
}

void hello(const char *username) {
    char safe_username[MAX_USERNAME_LENGTH * 6 + 1]; // Worst case scenario for HTML escaping
    escape(safe_username, username);
    printf("Hello %s\n", safe_username);
}

int main() {
    const char *url = "/hello/username";
    if (strncmp(url, "/hello/", 7) == 0) {
        const char *username = url + 7;
        hello(username);
    }
    return 0;
}