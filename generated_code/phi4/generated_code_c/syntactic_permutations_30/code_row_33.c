#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect_to(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <target_query> <default_url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target_query = argv[1];
    const char *default_url = argv[2];

    regex_t regex;
    int reti;

    // Compile regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    // Execute regular expression
    reti = regexec(&regex, target_query, 0, NULL, 0);

    if (!reti) {
        redirect_to(target_query);
    } else if (reti == REG_NOMATCH) {
        redirect_to(default_url);
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    }

    // Free compiled regular expression if you want to use the regex_t again
    regfree(&regex);

    return EXIT_SUCCESS;
}