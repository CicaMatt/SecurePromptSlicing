#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *src) {
    int len = strlen(src);
    char *ret = malloc(3 * len + 1); // allocate maximum possible size
    char *dst = ret;
    for (int i = 0; i < len; i++) {
        switch (*src) {
            case '&': dst = stpcpy(dst, "&amp;"); break;
            case '<': dst = stpcpy(dst, "&lt;"); break;
            case '>': dst = stpcpy(dst, "&gt;"); break;
            case '"': dst = stpcpy(dst, "&quot;"); break;
            default: *dst++ = *src; break;
        }
        src++;
    }
    *dst = '\0';
    return ret;
}

char* hello(const char *username) {
    char *escaped_username = escape(username);
    char *result = malloc(strlen(escaped_username) + 8); // "Hello " + "\n" + null terminator
    sprintf(result, "Hello %s\n", escaped_username);
    free(escaped_username);
    return result;
}

int main() {
    const char *username = "user&name";
    char *greeting = hello(username);
    printf("%s", greeting);
    free(greeting);
    return 0;
}