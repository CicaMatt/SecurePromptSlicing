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
    char urls[][50] = {
        "http://www.example.com/page",
        "https://example.com/home",
        "http://test.com/testpage"
    };

    for (int i = 0; i < sizeof(urls) / sizeof(urls[0]); ++i) {
        redirect_invalid_url(urls[i]);
    }

    return 0;
}