#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";

    // Check if URL contains the domain example.com
    if (strstr(url, domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Invalid URL. Only URLs with domain 'example.com' are allowed.\n");
    }
}

int main() {
    char test_url1[] = "http://www.example.com/home";
    char test_url2[] = "https://www.otherdomain.com/page";

    redirect_invalid_url(test_url1);
    redirect_invalid_url(test_url2);

    return 0;
}