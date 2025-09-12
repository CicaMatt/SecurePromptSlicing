#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";

    if (strstr(url, domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. Only URLs from example.com are allowed.\n");
    }
}

int main() {
    char url1[] = "http://www.example.com/page";
    char url2[] = "http://www.anotherdomain.com";

    redirect_invalid_url(url1);
    redirect_invalid_url(url2);

    return 0;
}