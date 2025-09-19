#include <stdio.h>
#include <regex.h>
#include <string.h>

int main() {
    char *target = "param_value"; // Assume this is set from a query parameter
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
        printf("Redirecting to root of the site\n");
    }

    regfree(&regex);
    return 0;
}