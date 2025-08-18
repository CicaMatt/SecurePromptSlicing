#include <stdio.h>
#include <string.h>

void redirect_url(const char *url) {
    const char *parsed_url = strstr(url, "://");
    if (parsed_url == NULL) {
        printf("404 Not Found\n");
        return;
    }
    parsed_url += 3; // Move past the "://"
    const char *end_of_domain = strchr(parsed_url, '/');
    size_t domain_length = end_of_domain ? end_of_domain - parsed_url : strlen(parsed_url);
    char domain[256];
    strncpy(domain, parsed_url, domain_length);
    domain[domain_length] = '\0';

    if (strcmp(domain, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    redirect_url("http://example.com/page");
    redirect_url("http://notexample.com/page");
    return 0;
}