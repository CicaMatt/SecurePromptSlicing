#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void handle_request(const char *target) {
    regex_t regex;
    int reti;

    if (regcomp(&regex, ".*example\\.com", REG_EXTENDED | REG_NOSUB)) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    if ((reti = regexec(&regex, target, 0, NULL, 0)) == 0) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Redirecting to: /\n");
    }

    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);

    return EXIT_SUCCESS;
}