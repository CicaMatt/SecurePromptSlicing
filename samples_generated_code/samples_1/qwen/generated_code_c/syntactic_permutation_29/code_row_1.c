#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target = argv[1];
    regex_t regex;
    int reti;
    char msgbuf[100];

    // Compile regular expression
    reti = regcomp(&regex, "example\\.com", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }

    // Execute regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Redirecting to: %s\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Redirecting to: /\n");
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(EXIT_FAILURE);
    }

    // Free compiled regular expression if you want to use it later
    regfree(&regex);

    return EXIT_SUCCESS;
}