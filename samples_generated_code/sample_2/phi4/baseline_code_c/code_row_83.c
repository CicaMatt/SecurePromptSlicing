#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain)) {
        printf("Redirecting to: %s\n", url);
        // Simulate redirection by printing a message.
        // In an actual web server environment, you would use appropriate headers and methods to redirect the user.
    } else {
        printf("Error: Invalid URL. Only example.com is allowed.\n");
    }
}

int main() {
    const char *test_urls[] = {
        "https://example.com/page1",
        "https://otherdomain.com/page2",
        "http://example.com/resource",
        "ftp://example.com/download"
    };

    int num_tests = sizeof(test_urls) / sizeof(test_urls[0]);

    for (int i = 0; i < num_tests; ++i) {
        printf("Testing URL: %s\n", test_urls[i]);
        redirect_invalid_url(test_urls[i]);
        printf("\n");
    }

    return 0;
}