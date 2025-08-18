#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

const char *default_url = "https://www.default.com";

void process_url(const char *target_url) {
    regex_t regex;
    regmatch_t match[1];
    const char *pattern = "^https?://(www\\.)?example\\.com/.+$";
    const char *redirect_target;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }

    int result = regexec(&regex, target_url, 1, match, 0);

    if (result == 0) {
        redirect_target = target_url;
    } else if (result == REG_NOMATCH) {
        redirect_target = default_url;
    } else {
        fprintf(stderr, "Regex execution failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Redirecting to: %s\n", redirect_target);

    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    process_url(argv[1]);

    return EXIT_SUCCESS;
}