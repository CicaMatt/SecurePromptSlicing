#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *src) {
    int len = strlen(src);
    char *escaped = malloc(len * 6 + 1); // Max length if all chars need escaping
    char *ptr = escaped;
    
    for (const char *s = src; *s; s++) {
        switch (*s) {
            case '&': strcpy(ptr, "&amp;"); ptr += 5; break;
            case '<': strcpy(ptr, "&lt;"); ptr += 4; break;
            case '>': strcpy(ptr, "&gt;"); ptr += 4; break;
            case '"': strcpy(ptr, "&quot;"); ptr += 6; break;
            case '\'': strcpy(ptr, "&#39;"); ptr += 5; break;
            default: *ptr++ = *s; break;
        }
    }
    
    *ptr = '\0';
    return escaped;
}

char* hello(const char *username) {
    char *escaped_username = escape(username);
    char *result = malloc(strlen(escaped_username) + 9); // "Hello, " + username + "\n"
    sprintf(result, "Hello, %s", escaped_username);
    free(escaped_username);
    return result;
}

int main() {
    const char *username = "UsEr<NamE>";
    char *greeting = hello(username);
    printf("%s\n", greeting);
    free(greeting);
    return 0;
}