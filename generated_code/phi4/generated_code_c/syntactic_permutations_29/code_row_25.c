#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

int starts_with_example_com(const char *url) {
    const char *pattern = "example\\.com";
    return strstr(url, pattern) != NULL;
}

void redirect_user(const char *target) {
    if (starts_with_example_com(target)) {
        printf("Location: /\n\n");
    } else {
        printf("Location: %s\n\n", target);
    }
}

int main() {
    const char *url_query = "GET /redirect?target=https://example.com/page HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";

    char *method, *path, *http_version;
    char target[MAX_URL_LENGTH] = {0};

    sscanf(url_query, "%s %s %s", method, path, http_version);

    if (strncmp(path, "/redirect?", 9) == 0) {
        sscanf(path + 9, "target=%[^\r\n]", target);
        
        redirect_user(target);
    } else {
        printf("Location: /\n\n");
    }

    return 0;
}