#include <stdio.h>
#include <string.h>

void redirect_url(const char *url) {
    const char *redirect_domain = "example.com";
    char netloc[256] = {0};

    // Parse the URL to get the network location (domain)
    const char *netloc_start = strstr(url, "//") + 2;
    if (!netloc_start) {
        printf("404 error\n");
        return;
    }

    const char *next_slash = strchr(netloc_start, '/');
    if (!next_slash || strlen(next_slash) > sizeof(netloc) - 1) {
        strcpy(netloc, netloc_start);
    } else {
        strncpy(netloc, netloc_start, next_slash - netloc_start);
    }

    // Check if the domain is "example.com"
    if (strcmp(netloc, redirect_domain) == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("404 error\n");
    }
}

int main() {
    const char *url1 = "http://example.com/path/to/resource";
    const char *url2 = "http://anotherdomain.com/path";

    redirect_url(url1); // Should redirect
    redirect_url(url2); // Should give 404 error

    return 0;
}