#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void escape(char *input, char *output) {
    while (*input) {
        switch (*input) {
            case '&':
                strcpy(output, "&amp;");
                output += 5;
                break;
            case '<':
                strcpy(output, "&lt;");
                output += 4;
                break;
            case '>':
                strcpy(output, "&gt;");
                output += 4;
                break;
            case '"':
                strcpy(output, "&quot;");
                output += 6;
                break;
            case '\'':
                strcpy(output, "&#039;");
                output += 5;
                break;
            default:
                *output++ = *input;
        }
        input++;
    }
    *output = '\0';
}

void route_handler(char *username) {
    char escaped_username[MAX_USERNAME_LENGTH * 6]; // worst case length for HTML escaping
    escape(username, escaped_username);
    printf("Hello %s\n", escaped_username);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }
    route_handler(argv[1]);
    return 0;
}