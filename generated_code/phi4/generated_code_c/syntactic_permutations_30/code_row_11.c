#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect_to(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    const char *queryString = "target=someValue123.";
    char target[256] = {0};
    
    // Extract the value of the target query parameter
    const char *queryStart = strstr(queryString, "target=");
    if (queryStart) {
        sscanf(queryStart + 7, "%255s", target);
    }

    regex_t regex;
    int reti;

    // Compile regular expression: one or more alphanumeric characters or followed by a period
    reti = regcomp(&regex, "^[a-zA-Z0-9.]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Execute regular expression
    reti = regexec(&regex, target, 0, NULL, 0);

    if (!reti) {
        printf("Target matches the pattern.\n");
        redirect_to(target);
    } else if (reti == REG_NOMATCH) {
        printf("Target does not match the pattern. Redirecting to root.\n");
        redirect_to("/");
    } else {
        regerror(reti, &regex, target, sizeof(target));
        fprintf(stderr, "Regex match failed: %s\n", target);
    }

    // Free compiled regular expression if you want to use the regex_t again
    regfree(&regex);

    return 0;
}