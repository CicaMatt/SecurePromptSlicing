#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    const char *query = "example-target";  // Example query parameter value, replace as needed
    const char *root_url = "/";
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    reti = regexec(&regex, query, 0, NULL, 0);
    if (!reti) {
        redirect(query); // Redirect to target if it matches
    } else if (reti == REG_NOMATCH) {
        redirect(root_url); // Redirect to root if not matched
    } else {
        regfree(&regex);
        fprintf(stderr, "Regex match failed\n");
        return 1;
    }

    regfree(&regex);
    return 0;
}