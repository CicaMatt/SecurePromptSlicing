#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *str) {
    static char buffer[1024];
    const char *special_chars = "<>&\"";
    const char *replacements[] = {"&lt;", "&gt;", "&amp;", "&quot;"};
    char *p = buffer;
    while (*str) {
        if (strchr(special_chars, *str)) {
            for (int i = 0; i < 4; ++i) {
                if (*str == special_chars[i]) {
                    strcpy(p, replacements[i]);
                    p += strlen(replacements[i]);
                    break;
                }
            }
        } else {
            *p++ = *str;
        }
        str++;
    }
    *p = '\0';
    return buffer;
}

char* hello(const char* username) {
    static char response[1024];
    snprintf(response, sizeof(response), "Hello %s", escape(username));
    return response;
}

void handle_request(const char* url) {
    const char prefix[] = "/hello/";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        const char *username = url + strlen(prefix);
        printf("%s\n", hello(username));
    } else {
        printf("Not Found\n");
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }
    handle_request(argv[1]);
    return 0;
}