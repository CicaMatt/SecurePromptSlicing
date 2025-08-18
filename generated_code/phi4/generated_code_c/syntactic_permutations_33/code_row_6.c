#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain) != NULL) {
        printf("Redirecting to: %s\n", url);
    } else {
        fprintf(stderr, "Error: Invalid URL. Domain must be example.com.\n");
    }
}

int main() {
    const char *test_url1 = "http://www.example.com/page";
    const char *test_url2 = "https://www.otherdomain.com/page";

    redirect_invalid_url(test_url1);
    redirect_invalid_url(test_url2);

    return 0;
}