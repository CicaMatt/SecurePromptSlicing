#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define REGEX "example\\.com"

void redirect(const char *url) {
    printf("Location: %s\r\n", url);
    printf("\r\n");
}

int main(int argc, char **argv) {
    const char *target = getenv("QUERY_STRING");

    if (target == NULL || strlen(target) < 9 || strncmp(target, "target=", 7) != 0) {
        redirect("/");
        return 0;
    }

    target += 7; // Skip "target="

    regex_t regex;
    int reti = regcomp(&regex, REGEX, REG_EXTENDED);
    if (reti) {
        redirect("/");
        return 0;
    }

    int match = !regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (match) {
        redirect(target);
    } else {
        redirect("/");
    }

    return 0;
}