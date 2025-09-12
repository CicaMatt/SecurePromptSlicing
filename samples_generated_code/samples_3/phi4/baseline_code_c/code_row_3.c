#include <stdio.h>
#include <string.h>

void handle_redirect(const char *url) {
    const char *base_url = "example.com";
    if (strstr(url, base_url)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. Only URLs from example.com are allowed.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    handle_redirect(argv[1]);

    return 0;
}