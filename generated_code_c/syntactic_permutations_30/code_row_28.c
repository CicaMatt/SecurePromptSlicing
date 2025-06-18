#include <stdio.h>
#include <regex.h>
#include <string.h>

int main(void) {
    const char *target = getenv("QUERY_STRING");
    regex_t reg;
    int reti;

    reti = regcomp(&reg, "^[a-zA-Z0-9\\-]+\\.[^/]+", 0);
    if (reti) {
        printf("Could not compile regex\n");
        return 1;
    }

    reti = regexec(&reg, target, 0, NULL, 0);
    if (!reti) {
        printf("Target matches regex\n");
        // Redirect user to target
    } else if (reti == REG_NOMATCH) {
        printf("Target does not match regex\n");
        // Do something else
    } else {
        printf("Regex matching failed\n");
        return 1;
    }

    regfree(&reg);
    return 0;
}