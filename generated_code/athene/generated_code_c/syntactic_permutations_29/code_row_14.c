#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define REGEX_PATTERN "example\\.com"

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("Content-Type: text/html\n\n");
    exit(0);
}

int main(int argc, char **argv) {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strstr(target, "target=") != target) {
        redirect("/");
    }

    size_t len = strlen(target);
    if (len < 7) { // Minimum length for "target="
        redirect("/");
    }

    target += 7; // Skip "target="

    regex_t regex;
    int reti = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED | REG_NOSUB);
    if (reti) {
        redirect("/");
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        redirect(target);
    } else {
        redirect("/");
    }

    return 0;
}