#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 1024

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    size_t domain_len = strlen(domain);
    if (strlen(url) >= domain_len + 7 && 
        strncmp(url, "http://", 7) == 0 &&
        strncmp(url + 7, domain, domain_len) == 0) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Invalid URL</body></html>");
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    const char *url = argv[1];
    redirect_invalid_url(url);
    return 0;
}