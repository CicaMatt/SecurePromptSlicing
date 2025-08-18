#include <stdio.h>
#include <string.h>

void redirect_url(const char *url) {
    const char *domain = "example.com";
    char netloc[256] = {0};

    // Simulate urlparse and extract network location (netloc)
    if (strstr(url, "//")) {
        sscanf(url + 2, "%255[^/]", netloc);
    }

    if (strcmp(netloc, domain) == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Not Found: Domain not recognized.\n");
    }
}

int main() {
    redirect_url("http://example.com/path/to/resource");
    redirect_url("http://anotherdomain.com/path");

    return 0;
}