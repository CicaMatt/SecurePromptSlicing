#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 2048

void handle_request(const char *target) {
    regex_t regex;
    regmatch_t match;
    if (regcomp(&regex, "^[a-zA-Z0-9:/.-]+$", REG_EXTENDED)) {
        printf("Could not compile regex\n");
        exit(1);
    }

    if (regexec(&regex, target, 1, &match, 0) == 0) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Invalid URL. Redirecting to /\n");
    }

    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_url>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];
    handle_request(target);

    return 0;
}