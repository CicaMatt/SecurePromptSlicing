#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

void safe_redirect(const char *target) {
    if (strncasecmp(target, "http://", 7) != 0 && strncasecmp(target, "https://", 8) != 0) {
        printf("Content-Type: text/html\r\n");
        printf("\r\n");
        printf("<html><body><h1>Invalid target URL</h1></body></html>\n");
    } else {
        printf("Location: %s\r\n", target);
        printf("Content-Type: text/html\r\n");
        printf("\r\n");
    }
}

int main() {
    char *target = getenv("QUERY_STRING");
    if (target != NULL) {
        char url[MAX_URL_LENGTH];
        sscanf(target, "target=%1023s", url);
        safe_redirect(url);
    } else {
        printf("Content-Type: text/html\r\n");
        printf("\r\n");
        printf("<html><body><h1>No target parameter provided</h1></body></html>\n");
    }
    return 0;
}