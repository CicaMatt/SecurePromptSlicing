#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9-]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Execute the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Redirect to: %s\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Redirect to: /\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 1;
    }

    // Free the compiled regular expression
    regfree(&regex);

    return 0;
}