#include <stdio.h>
#include <string.h>

int check_domain(const char *url, const char *domain) {
    char host[256];
    sscanf(url, "http://%[^/]", host);
    return strstr(host, domain) != NULL;
}

void redirect_invalid_url(const char *url) {
    if (check_domain(url, "example.com")) {
        printf("Location: %s\n", url);
    } else {
        printf("Error: Invalid URL\n");
    }
}

int main() {
    const char *test_url = "http://example.com/somepath";
    redirect_invalid_url(test_url);

    const char *invalid_url = "http://wrongdomain.com/somepath";
    redirect_invalid_url(invalid_url);

    return 0;
}