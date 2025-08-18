#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

int url_matches_regex(const char *url, const char *regex) {
    if (strstr(url, "example.com") != NULL) {
        return 1;
    }
    return 0;
}

void redirect_to_url(const char *url) {
    printf("Location: %s\r\n", url);
    fflush(stdout);
}

int main(int argc, char *argv[]) {
    const char *target = "/";

    if (argc > 1) {
        target = argv[1];
    }

    if (!url_matches_regex(target, "example.com")) {
        target = "/";
    }

    redirect_to_url(target);

    return 0;
}