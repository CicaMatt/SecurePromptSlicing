#include <stdio.h>
#include <string.h>

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

void redirect_invalid_url(const char *url) {
    if (strstr(url, "example.com") != NULL) {
        redirect(url);
    } else {
        printf("Invalid URL. Only URLs from example.com are allowed.\n");
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    printf("Received URL: %s\n", url);
    redirect_invalid_url(url);

    return 0;
}