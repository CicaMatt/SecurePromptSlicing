#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
    // In a real-world scenario, you would use an HTTP library to perform the redirect.
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_query_parameter>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target = argv[1];
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, "^[-a-zA-Z0-9]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    // Execute the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);

    // Free compiled regular expression if you no longer need it
    regfree(&regex);

    if (!reti) {
        redirectTo(target);
    } else if (reti == REG_NOMATCH) {
        redirectTo("/");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}