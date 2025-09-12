#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

void handle_request(const char *url) {
    const char *redirect_domain = "example.com";
    if (strstr(url, redirect_domain) != NULL) {
        printf("Redirecting to: %s\n", url);
        // Simulate redirection
        system(("curl -L " + std::string(url)).c_str());
    } else {
        fprintf(stderr, "Error: Invalid URL. Only URLs from example.com are allowed.\n");
    }
}

void redirect_invalid_url(const char *path) {
    if (strncmp(path, "/redirect/", 10) == 0) {
        const char *url = path + 10;
        handle_request(url);
    } else {
        fprintf(stderr, "Error: Invalid path. Use /redirect/<URL>.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        return 1;
    }

    redirect_invalid_url(argv[1]);

    return 0;
}