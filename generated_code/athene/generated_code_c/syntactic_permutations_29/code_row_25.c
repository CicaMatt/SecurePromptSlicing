#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define REGEX "example\\.com"

void redirect(const char *location) {
    printf("Location: %s\r\n", location);
    printf("\r\n");
    exit(0);
}

int main(int argc, char **argv) {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strstr(target, "target=") != target) {
        redirect("/");
    }

    target += 7; // Skip "target="
    
    regex_t regex;
    int reti;
    reti = regcomp(&regex, REGEX, REG_ICASE);
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