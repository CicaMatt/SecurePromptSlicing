#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define REDIRECT_LOCATION "/"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];
    regex_t regex;
    int reti;

    // Compile regular expression
    reti = regcomp(&regex, ".*example\\.com.*", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Execute regular expression
    regmatch_t match;
    reti = regexec(&regex, target, 1, &match, 0);

    if (!reti) {
        printf("Redirect: Location: %s\n", target);
    } else {
        printf("Redirect: Location: %s\n", REDIRECT_LOCATION);
    }

    // Free memory allocated to the pattern buffer by regcomp()
    regfree(&regex);

    return 0;
}