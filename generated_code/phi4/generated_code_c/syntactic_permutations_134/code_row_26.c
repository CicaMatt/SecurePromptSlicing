#include <stdio.h>
#include <string.h>

const char* escape(const char* input) {
    static char buffer[256];
    const char *src = input;
    char *dst = buffer;

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
                strcpy(dst, "&quot;");
                dst += 6;
                break;
            case '\'':
                strcpy(dst, "&#39;");
                dst += 5;
                break;
            default:
                *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
    return buffer;
}

const char* hello(const char* username) {
    static char response[256];
    snprintf(response, sizeof(response), "Hello %s", escape(username));
    return response;
}

void handle_request(const char* url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        const char* username = url + 7;
        printf("%s\n", hello(username));
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Example usage
    handle_request("/hello/John Doe & Friends<>");
    return 0;
}