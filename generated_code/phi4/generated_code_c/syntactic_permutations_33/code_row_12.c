#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    
    if (strstr(url, domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. Only URLs with the domain '%s' are allowed.\n", domain);
    }
}

int main() {
    char test_url1[] = "http://www.example.com/page";
    char test_url2[] = "https://www.otherdomain.com/home";

    redirect_invalid_url(test_url1);
    redirect_invalid_url(test_url2);

    return 0;
}