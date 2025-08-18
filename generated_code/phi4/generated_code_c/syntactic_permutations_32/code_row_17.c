#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void redirect_invalid_url(const char *url) {
    const char *valid_domain = "example.com";

    // Check if the url contains the domain example.com
    if (strstr(url, valid_domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. Only URLs from example.com are allowed.\n");
    }
}

int main(int argc, char *argv[]) {
    char url[BUFFER_SIZE];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    strncpy(url, argv[1], BUFFER_SIZE - 1);
    url[BUFFER_SIZE - 1] = '\0'; // Ensure null termination

    redirect_invalid_url(url);

    return 0;
}