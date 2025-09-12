#include <stdio.h>
#include <regex.h>
#include <string.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
}

int main() {
    const char *query = "target=example-123.";
    const char *root = "/";
    regex_t regex;
    int reti;
    char msgbuf[100];

    // Extract target from query
    const char *target = strstr(query, "target=");
    if (target) {
        target += 7; // skip "target="
    } else {
        redirect(root);
        return 0;
    }

    // Compile regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Match target against regex
    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        redirect(target);
    } else if (reti == REG_NOMATCH) {
        redirect(root);
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 1;
    }

    // Free compiled regex
    regfree(&regex);

    return 0;
}