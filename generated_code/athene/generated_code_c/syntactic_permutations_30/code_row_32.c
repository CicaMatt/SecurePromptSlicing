#include <stdio.h>
#include <regex.h>
#include <string.h>

int main() {
    char *target = "example-target.";
    regex_t regex;
    int reti;
    char msgbuf[100];

    if (regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED) != 0) {
        printf("Could not compile regex\n");
        return 1;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Redirecting to: .\n");
    }

    regfree(&regex);
    return 0;
}