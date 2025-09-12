#include <stdio.h>
#include <string.h>
#include <regex.h>

#define MAX_TARGET_LENGTH 256

void handle_request(const char *target) {
    regex_t regex;
    regmatch_t match;

    if (regcomp(&regex, ".*example\\.com", REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    if (regexec(&regex, target, 1, &match, 0) == 0) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Redirecting to: /\n");
    }

    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];
    handle_request(target);

    return 0;
}