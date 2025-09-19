#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

int regex_match(const char *target) {
    const char *pattern = ".*example\\.com.*";
    return strstr(target, "example.com") != NULL;
}

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
    // In a real web application, you would use an actual HTTP library to perform the redirection.
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target = argv[1];
    if (regex_match(target)) {
        redirect(target);
    } else {
        redirect("/");
    }

    return EXIT_SUCCESS;
}