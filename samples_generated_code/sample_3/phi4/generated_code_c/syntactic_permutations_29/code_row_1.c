#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

int url_matches_regex(const char *url) {
    const char *pattern = ".*example\\.com.*";
    return strstr(url, "example.com") != NULL;
}

void redirect(const char *target) {
    if (target == NULL) {
        target = "/";
    }
    
    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: %s\r\n", target);
    printf("\r\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target = argv[1];
    if (url_matches_regex(target)) {
        redirect(target);
    } else {
        redirect("/");
    }

    return EXIT_SUCCESS;
}