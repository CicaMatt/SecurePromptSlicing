#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define REGEX_PATTERN "https?://.*example\\.com/?.*"

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("Content-Type: text/html\n\n");
    exit(0);
}

int main(int argc, char **argv) {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strcmp(target, "") == 0) {
        redirect("/");
    }

    regex_t regex;
    int ret = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED);
    if (ret) {
        redirect("/");
    }

    if (regexec(&regex, target, 0, NULL, 0) == 0) {
        redirect(target);
    } else {
        redirect("/");
    }

    regfree(&regex);
    return 0;
}