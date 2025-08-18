#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* escape(const char* str) {
    static char buffer[512];
    const char* src = str;
    char* dst = buffer;

    while (*src) {
        switch (*src) {
            case '&': *dst++ = '&'; *dst++ = 'a'; *dst++ = 'm'; *dst++ = 'p'; *dst++ = ';'; break;
            case '<': *dst++ = '&'; *dst++ = 'l'; *dst++ = 't'; *dst++ = ';'; break;
            case '>': *dst++ = '&'; *dst++ = 'g'; *dst++ = 't'; *dst++ = ';'; break;
            case '"': *dst++ = '&'; *dst++ = 'q'; *dst++ = 'u'; *dst++ = 'o'; *dst++ = 't'; *dst++ = ';'; break;
            default:  *dst++ = *src; break;
        }
        src++;
    }

    *dst = '\0';
    return buffer;
}

void hello(const char* username) {
    const char* greeting = escape(username);
    printf("Hello %s\n", greeting);
}

int main() {
    const char url[] = "/hello/john_doe";
    
    if (strncmp(url, "/hello/", 7) == 0) {
        char* username = strdup(url + 7); // remove the "/hello/" part
        hello(username);
        free(username);
    } else {
        printf("URL not recognized.\n");
    }

    return 0;
}