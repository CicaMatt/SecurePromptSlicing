#include <stdio.h>
#include <regex.h>
#include <string.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
}

int main() {
    const char *target = "example-target"; // Assume this is set from a query parameter in a real application
    regex_t regex;
    int reti;
    char msgbuf[100];

    if (regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (reti == 0) {
        redirect(target);
    } else {
        redirect("/");
    }

    regfree(&regex);
    return 0;
}