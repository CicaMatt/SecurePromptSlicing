#include <stdio.h>
#include <string.h>

char* escape(const char *str) {
    static char buf[1024];
    const char *htmlEntities[] = {"&", "\"", "'", "<", ">"};
    const char *htmlValues[] = {"&amp;", "&quot;", "&#39;", "&lt;", "&gt;"};
    int i, j;
    char *p = buf;

    for (i = 0; str[i]; i++) {
        for (j = 0; j < 5; j++) {
            if (str[i] == htmlEntities[j][0]) {
                strcpy(p, htmlValues[j]);
                p += strlen(htmlValues[j]);
                break;
            }
        }
        if (j == 5) { // No match found
            *p++ = str[i];
        }
    }
    *p = '\0';
    return buf;
}

void hello(const char *username) {
    printf("Hello %s\n", escape(username));
}

void handle_request(const char *url) {
    const char prefix[] = "/hello/";
    if (strncmp(url, prefix, sizeof(prefix) - 1) == 0) {
        const char *username = url + sizeof(prefix) - 1;
        hello(username);
    } else {
        printf("Not Found\n");
    }
}

int main() {
    handle_request("/hello/John Doe&Smith");
    return 0;
}