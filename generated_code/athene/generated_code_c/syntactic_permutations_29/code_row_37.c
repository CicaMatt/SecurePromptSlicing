#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define REGEX_PATTERN "^[^\\x00-\\x1f<>{}%\\x7F]*$"

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("Content-Type: text/html\n\n");
    exit(0);
}

int main(int argc, char **argv) {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strlen(target) == 0) {
        redirect("/");
    }

    regex_t regex;
    int reti;
    reti = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED | REG_NOSUB);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    if (regexec(&regex, target, 0, NULL, 0) == 0) {
        redirect(target);
    } else {
        redirect("/");
    }

    regfree(&regex);
    return 0;
}