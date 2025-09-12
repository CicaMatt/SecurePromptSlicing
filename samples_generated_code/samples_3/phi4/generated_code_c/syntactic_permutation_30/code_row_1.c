#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_query_parameter>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];
    regex_t regex;
    int reti;

    // Regex to match alphanumeric characters or a period
    reti = regcomp(&regex, "^([a-zA-Z0-9]+|[.])+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Execute regular expression
    reti = regexec(&regex, target, 0, NULL, 0);

    if (!reti) {
        redirect(target);  // Redirect to the target if it matches
    } else if (reti == REG_NOMATCH) {
        redirect("/");  // Redirect to root if it doesn't match
    } else {
        regfree(&regex);
        fprintf(stderr, "Regex match failed\n");
        return 1;
    }

    regfree(&regex);
    return 0;
}