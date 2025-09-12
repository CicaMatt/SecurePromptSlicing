#include <stdio.h>
#include <regex.h>
#include <string.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
}

int main() {
    const char *target = "example-target"; // This should be the value of the target query parameter
    regex_t regex;
    int reti;

    if (regcomp(&regex, "^[a-zA-Z0-9-]+", REG_EXTENDED) != 0) {
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