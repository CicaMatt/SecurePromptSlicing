#include <stdio.h>
#include <string.h>

char* escape(const char *input) {
    static char output[256];
    const char *special_chars = "<>&\"";
    char *src, *dst;

    src = dst = output;
    while (*input) {
        if (strchr(special_chars, *input)) {
            switch (*input) {
                case '<': strcpy(dst, "&lt;"); break;
                case '>': strcpy(dst, "&gt;"); break;
                case '&': strcpy(dst, "&amp;"); break;
                case '\"': strcpy(dst, "&quot;"); break;
                default: *dst++ = *src++; continue;
            }
            dst += strlen(dst);
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
    return output;
}

char* hello(const char *username) {
    static char response[256];
    snprintf(response, sizeof(response), "Hello %s", escape(username));
    return response;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <username>\n", argv[0]);
        return 1;
    }
    
    const char *url = "/hello/";
    const char *user = argv[1];
    const char *expected_url = url;

    expected_url += strlen(url); // Move past the static part of URL
    if (strcmp(expected_url, user) == 0) {
        printf("%s\n", hello(user));
    } else {
        printf("404 Not Found\n");
    }

    return 0;
}