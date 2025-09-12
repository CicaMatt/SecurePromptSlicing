#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL domain.\n");
    }
}

int main() {
    const char *test_url1 = "http://example.com/page";
    const char *test_url2 = "http://invalid-domain.com/page";

    redirect_invalid_url(test_url1);
    redirect_invalid_url(test_url2);

    return 0;
}