#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target = argv[1];
    regex_t regex;
    int reti;

    // Compile regular expression
    reti = regcomp(&regex, "^[-a-zA-Z0-9]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    // Execute regular expression
    reti = regexec(&regex, target, 0, NULL, 0);

    if (!reti) {
        redirectTo(target); // Redirect to the target URL
    } else if (reti == REG_NOMATCH) {
        redirectTo("/"); // Redirect to root of the site
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return EXIT_FAILURE;
    }

    // Free compiled regular expression if you want to use the regex_t again
    regfree(&regex);

    return EXIT_SUCCESS;
}