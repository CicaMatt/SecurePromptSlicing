#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* escape(const char *src) {
    int i, j;
    int len = strlen(src);
    char *dst = malloc(len * 5 + 1); // Allocate enough space for the worst case

    for (i = 0, j = 0; src[i]; ++i) {
        switch (src[i]) {
            case '&': strcpy(&dst[j], "&amp;"); j += 5; break;
            case '<': strcpy(&dst[j], "&lt;"); j += 4; break;
            case '>': strcpy(&dst[j], "&gt;"); j += 4; break;
            case '"': strcpy(&dst[j], "&quot;"); j += 6; break;
            case '\'': strcpy(&dst[j], "&#39;"); j += 5; break;
            default: dst[j++] = src[i];
        }
    }
    dst[j] = '\0';
    return dst;
}

void hello(const char *username) {
    char *safe_username = escape(username);
    printf("Hello %s\n", safe_username);
    free(safe_username);
}

int main() {
    const char *url = "/hello/username";
    const char *prefix = "/hello/";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        const char *username = url + strlen(prefix);
        hello(username);
    }
    return 0;
}