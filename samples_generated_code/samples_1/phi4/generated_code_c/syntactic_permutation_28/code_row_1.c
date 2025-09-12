#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define REGEX_SIZE 256

void handle_url(const char *target_url, const char *pattern) {
    regex_t regex;
    int reti;

    // Compile regular expression
    if (regcomp(&regex, pattern, REGEX_CFLAGS) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }

    // Execute regular expression
    reti = regexec(&regex, target_url, 0, NULL, 0);

    if (!reti) {
        printf("Match found: Redirecting to %s\n", target url);
    } else if (reti == REG_NOMATCH) {
        printf("No match found: Using the original URL %s\n", target_url);
    } else {
        char msgbuf[1024];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(EXIT_FAILURE);
    }

    // Free compiled regular expression if you want to use the regex_t again
    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <target_url> <pattern>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *target_url = argv[1];
    const char *pattern = argv[2];

    handle_url(target_url, pattern);

    return EXIT_SUCCESS;
}