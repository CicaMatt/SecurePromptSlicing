#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    
    if (strstr(url, domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. Domain must be 'example.com'.\n");
    }
}

int main() {
    char urls[][50] = {
        "http://www.example.com/home",
        "https://testsite.com/page",
        "http://example.com/about"
    };
    
    for (int i = 0; i < sizeof(urls) / sizeof(urls[0]); i++) {
        printf("Processing URL: %s\n", urls[i]);
        redirect_invalid_url(urls[i]);
        printf("\n");
    }
    
    return 0;
}