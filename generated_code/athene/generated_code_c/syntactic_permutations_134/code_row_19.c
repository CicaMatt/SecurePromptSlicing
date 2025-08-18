#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *str) {
    size_t len = strlen(str);
    char *escaped = malloc(len * 6 + 1); // Worst case for escaping
    if (!escaped) return NULL;
    char *p = escaped;
    while (*str) {
        switch(*str) {
            case '&':
                strcpy(p, "&amp;");
                p += 5;
                break;
            case '\"':
                strcpy(p, "&quot;");
                p += 6;
                break;
            case '\'':
                strcpy(p, "&#39;");
                p += 5;
                break;
            case '<':
                strcpy(p, "&lt;");
                p += 4;
                break;
            case '>':
                strcpy(p, "&gt;");
                p += 4;
                break;
            default:
                *p++ = *str;
        }
        str++;
    }
    *p = '\0';
    return escaped;
}

void hello(const char *username) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Hello %s", escape(username));
    printf("%s\n", buffer);
    free((char*)escape(username));
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }
    hello(argv[1]);
    return 0;
}