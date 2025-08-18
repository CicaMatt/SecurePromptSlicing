#include <stdio.h>
#include <regex.h>
#include <string.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
}

int main() {
    const char *target = "example-target"; // Example target query parameter value
    regex_t regex;
    int reti;
    char msgbuf[100];

    if (regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (reti == REG_NOMATCH) {
        redirect("/");
    } else {
        redirect(target);
    }

    regfree(&regex);
    return 0;
}