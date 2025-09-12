#include <stdio.h>
#include <string.h>

void escape(char *input, char *output) {
    const char *html_escape[] = {"&", "&amp;", "<", "&lt;", ">", "&gt;,", "\"", "&quot;"};
    int i;
    while (*input) {
        for (i = 0; i < sizeof(html_escape)/2; i += 2) {
            if (*input == html_escape[i][0]) {
                strcpy(output, html_escape[i+1]);
                output += strlen(html_escape[i+1]);
                break;
            }
        }
        if (i >= sizeof(html_escape)) {
            *output++ = *input;
        }
        input++;
    }
    *output = '\0';
}

char* hello(char *username) {
    static char response[256];
    char escaped_username[256];
    escape(username, escaped_username);
    snprintf(response, sizeof(response), "Hello %s", escaped_username);
    return response;
}

int main(int argc, char **argv) {
    if (argc != 3 || strcmp(argv[1], "/hello/") != 0) {
        printf("Usage: %s /hello/ <username>\n", argv[0]);
        return 1;
    }
    char *result = hello(argv[2]);
    printf("%s\n", result);
    return 0;
}