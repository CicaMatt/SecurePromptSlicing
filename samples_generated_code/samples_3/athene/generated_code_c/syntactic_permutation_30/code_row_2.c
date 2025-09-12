#include <stdio.h>
#include <string.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
}

int main() {
    const char *target = "default"; // Example target query parameter
    regex_t regex;
    int reti;

    if (regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED)) {
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