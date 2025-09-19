#include <stdio.h>
#include <regex.h>
#include <string.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
}

int main() {
    const char *target = "example"; // Assume this is set from a query parameter
    regex_t regex;
    int reti;

    if (regcomp(&regex, "^[a-zA-Z0-9]+(\\.)?", REG_EXTENDED) != 0) {
        return 1; // Compilation failed
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