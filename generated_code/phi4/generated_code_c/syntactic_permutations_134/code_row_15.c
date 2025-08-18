#include <stdio.h>
#include <string.h>

char* escape(const char* input) {
    static char output[256];
    const char *src = input;
    char *dst = output;

    while (*src) {
        switch (*src) {
            case '&':
                strcpy(dst, "&amp;");
                dst += 5;
                break;
            case '<':
                strcpy(dst, "&lt;");
                dst += 4;
                break;
            case '>':
                strcpy(dst, "&gt;");
                dst += 4;
                break;
            case '"':
                *dst++ = '&';
                *dst++ = 'q';
                *dst++ = 'u';
                *dst++ = 'o';
                *dst++ = 't';
                *dst++ = ';';
                break;
            default:
                *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';

    return output;
}

void handle_request(const char* url) {
    if (strncmp(url, "//", 2) == 0) {
        const char* username = url + 2; // Strip the initial '//'
        printf("Hello %s\n", escape(username));
    } else {
        printf("Invalid URL\n");
    }
}

int main() {
    handle_request("//john_doe"); // Example usage
    return 0;
}