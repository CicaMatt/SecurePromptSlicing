#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *str) {
    size_t len = strlen(str);
    char *escaped_str = malloc(3 * len + 1); // Allocate enough space for replacements
    if (!escaped_str) return NULL;

    escaped_str[0] = '\0'; // Initialize as an empty string

    while (*str) {
        switch (*str) {
            case '&':
                strcat(escaped_str, "&amp;");
                break;
            case '<':
                strcat(escaped_str, "&lt;");
                break;
            case '>':
                strcat(escaped_str, "&gt;");
                break;
            case '"':
                strcat(escaped_str, "&quot;");
                break;
            case '\'':
                strcat(escaped_str, "&#39;");
                break;
            default:
                strncat(escaped_str, str, 1);
        }
        str++;
    }

    return escaped_str;
}

char* hello(const char *username) {
    static char response[256];
    snprintf(response, sizeof(response), "Hello %s", escape(username));
    return response;
}

void handle_request(const char *url) {
    const char *prefix = "/hello/";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        const char *username = url + strlen(prefix);
        printf("%s\n", hello(username));
    } else {
        printf("404 Not Found\n");
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);

    return EXIT_SUCCESS;
}