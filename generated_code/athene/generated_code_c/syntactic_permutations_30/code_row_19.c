#include <stdio.h>
#include <regex.h>

int main() {
    regex_t regex;
    int reti;
    char msgbuf[100];

    const char *pattern = "^[a-zA-Z0-9\\-]+\\.";
    const char *test_str = "target=query.";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Could not compile regex\n");
        return 1;
    }

    reti = regexec(&regex, test_str, 0, NULL, 0);
    if (!reti) {
        char *target = "query";
        printf("Target variable is set to: %s\n", target);
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    }

    regfree(&regex);
    return 0;
}