#include <stdio.h>
#include <regex.h>
#include <string.h>

void redirect(const char *location) {
    printf("Location: %s\r\n", location);
    printf("\r\n");
}

int main() {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strstr(target, "target=") != target) {
        target = "";
    } else {
        target += 7; // Skip "target="
    }

    regex_t regex;
    int reti;
    char msgbuf[100];

    const char *pattern = ".*example\\.com.*";
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
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