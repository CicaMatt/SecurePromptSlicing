#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 1024

void redirect_invalid_url(const char *url) {
    char domain[MAX_URL_LENGTH];
    sscanf(url, "http://%[^/]", domain);
    
    if (strcmp(domain, "example.com") == 0) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n\n");
        exit(0);
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Invalid URL</body></html>");
        exit(1);
    }
}

int main() {
    char *url = getenv("QUERY_STRING");
    if (url != NULL) {
        redirect_invalid_url(url);
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>URL parameter missing</body></html>");
    }
    return 0;
}