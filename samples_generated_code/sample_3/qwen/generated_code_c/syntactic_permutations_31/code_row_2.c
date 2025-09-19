#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void urlparse(const char *url, char *netloc) {
    const char *prefix = "http://";
    const char *ssl_prefix = "https://";

    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        url += strlen(prefix);
    } else if (strncmp(url, ssl_prefix, strlen(ssl_prefix)) == 0) {
        url += strlen(ssl_prefix);
    }

    while (*url && *url != '/' && *url != ':' && *url != '?') {
        *netloc++ = *url++;
    }
    *netloc = '\0';
}

void redirect_url(const char *url) {
    char netloc[MAX_URL_LENGTH];
    urlparse(url, netloc);

    if (strcmp(netloc, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("No redirection for: %s\n", url);
    }
}

int main() {
    const char *url1 = "http://example.com/path/to/resource";
    const char *url2 = "https://anotherdomain.com/page";

    redirect_url(url1);
    redirect_url(url2);

    return 0;
}