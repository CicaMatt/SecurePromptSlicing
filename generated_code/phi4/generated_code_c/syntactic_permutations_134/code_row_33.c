#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* escape(const char* str) {
    static char buffer[1024];
    const char *src = str;
    char *dst = buffer;

    while (*src) {
        switch (*src) {
            case '&':  strcat(dst, "&amp;"); dst += 5; break;
            case '<':  strcat(dst, "&lt;"); dst += 4; break;
            case '>':  strcat(dst, "&gt;"); dst += 4; break;
            case '"':  strcat(dst, "&quot;"); dst += 6; break;
            case '\'': strcat(dst, "&#39;"); dst += 5; break;
            default:   *dst++ = *src++;
        }
    }
    *dst = '\0';
    return buffer;
}

const char* hello(const char* username) {
    static char response[1024];
    snprintf(response, sizeof(response), "Hello %s", escape(username));
    return response;
}

int main() {
    const char* url = "/hello/john_doe";
    
    if (strncmp(url, "/hello/", 7) == 0) {
        const char* username = url + 7; // Skip the /hello/ part
        printf("%s\n", hello(username));
    } else {
        printf("404 Not Found\n");
    }

    return 0;
}