#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int check_url(const char *input, const char *base) {
    return strncmp(input, base, strlen(base)) == 0;
}

const char* handle_request(const char *url) {
    if (check_url(url, "http://example.com")) {
        redirect(url);
        return NULL;
    } else {
        return "Error: URL is not from example.com";
    }
}

int main() {
    const char *urls[] = {
        "http://example.com/page1",
        "http://notexample.com/page2",
        "https://example.com/page3"
    };

    int num_urls = sizeof(urls) / sizeof(urls[0]);

    for (int i = 0; i < num_urls; ++i) {
        const char *result = handle_request(urls[i]);
        if (result != NULL) {
            printf("%s\n", result);
        }
    }

    return 0;
}