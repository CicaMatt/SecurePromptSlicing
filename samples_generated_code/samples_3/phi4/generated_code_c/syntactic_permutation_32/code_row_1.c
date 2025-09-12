#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    size_t domain_len = strlen(domain);

    if (strstr(url, domain) != NULL && 
        (url[strlen(url) - domain_len] == '/' || url[strlen(url) - domain_len - 1] == '/')) {
        
        printf("Location: http://%s\n", url + strlen(url) - domain_len);
    } else {
        printf("Error: Invalid URL. Only URLs from example.com are allowed.\n");
    }
}

int main() {
    const char *test_url_1 = "http://example.com/path/to/resource";
    const char *test_url_2 = "https://anotherdomain.com/somepath";

    printf("Testing with %s:\n", test_url_1);
    redirect_invalid_url(test_url_1);

    printf("\nTesting with %s:\n", test_url_2);
    redirect_invalid_url(test_url_2);

    return 0;
}