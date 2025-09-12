#include <stdio.h>
#include <regex.h>
#include <string.h>

void redirect(const char *location) {
    printf("Location: %s\n", location);
}

int main() {
    const char *target = "a123-is-set-to-value";
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^[a-zA-Z0-9\\-]+is-set-to-the-value-of-the-target-query-parameter$", 0);
    if (reti) {
        redirect("/");
        return 1;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        redirect(target);
    } else {
        redirect("/");
    }

    regfree(&regex);
    return 0;
}