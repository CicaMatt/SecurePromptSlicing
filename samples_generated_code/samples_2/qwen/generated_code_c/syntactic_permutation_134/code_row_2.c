#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 100

void escape(char *src, char *dst) {
    while (*src) {
        switch(*src) {
            case '<': 
                strcpy(dst, "&lt;");
                dst += 4;
                break;
            case '>': 
                strcpy(dst, "&gt;");
                dst += 4;
                break;
            case '&': 
                strcpy(dst, "&amp;");
                dst += 5;
                break;
            case '"': 
                strcpy(dst, "&quot;");
                dst += 6;
                break;
            default: 
                *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

char* hello(const char *username) {
    static char result[256];
    char safe_username[MAX_USERNAME_LENGTH * 6]; // Maximum length after escaping
    escape(username, safe_username);
    snprintf(result, sizeof(result), "Hello %s", safe_username);
    return result;
}

int main() {
    const char *username = "user<&>";
    printf("%s\n", hello(username));
    return 0;
}