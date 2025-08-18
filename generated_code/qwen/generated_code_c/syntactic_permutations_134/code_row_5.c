#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *str) {
    int len = 0;
    const char *s;
    for (s = str; *s; ++s) len += (*s == '&' || *s == '<' || *s == '>') ? 5 : 1;

    char *result = malloc(len + 1);
    if (!result) return NULL;

    char *p = result;
    for (s = str; *s; ++s) {
        switch(*s) {
            case '&': strcpy(p, "&amp;"); p += 5; break;
            case '<': strcpy(p, "&lt;"); p += 4; break;
            case '>': strcpy(p, "&gt;"); p += 4; break;
            default: *p++ = *s; break;
        }
    }
    *p = '\0';
    return result;
}

void hello(const char *username) {
    char *escaped_username = escape(username);
    if (escaped_username) {
        printf("Hello %s\n", escaped_username);
        free(escaped_username);
    } else {
        printf("Memory allocation failed\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Simulating the URL path /hello/username
    hello(argv[1]);

    return EXIT_SUCCESS;
}