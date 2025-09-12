#include <stdio.h>
#include <string.h>

void escape(const char *input, char *output) {
    while (*input) {
        switch (*input) {
            case '&':
                strcpy(output, "&amp;");
                break;
            case '<':
                strcpy(output, "&lt;");
                break;
            case '>':
                strcpy(output, "&gt;");
                break;
            default:
                *output++ = *input;
        }
        input++;
        output++;
    }
    *output = '\0';
}

const char* hello(const char *username) {
    static char result[256];
    snprintf(result, sizeof(result), "Hello, %s!", username);
    return result;
}

void handle_request(const char *url) {
    const char *prefix = "/hello/";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        const char *username = url + strlen(prefix);
        char escaped_username[256];
        escape(username, escaped_username);

        printf("%s\n", hello(escaped_username));
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    char input_url[] = "/hello/John&Doe";
    handle_request(input_url);
    return 0;
}