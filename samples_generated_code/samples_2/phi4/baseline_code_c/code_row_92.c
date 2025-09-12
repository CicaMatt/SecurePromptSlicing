#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);

    // Check if the URL ends with example.com
    if (url_len >= domain_len &&
        strcmp(url + url_len - domain_len, domain) == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        fprintf(stderr, "Error: Invalid URL. Only URLs from example.com are allowed.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    redirect_invalid_url(argv[1]);
    return 0;
}