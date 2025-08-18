#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

int matches_regex(const char *target) {
    const char *pattern = ".*example\\.com.*";
    return strstr(target, "example.com") != NULL;
}

void handle_request(const char *target) {
    if (matches_regex(target)) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Redirecting to: /\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target = argv[1];
    handle_request(target);

    return EXIT_SUCCESS;
}