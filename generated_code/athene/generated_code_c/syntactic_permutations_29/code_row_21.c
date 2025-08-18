#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define REGEX "^https?://.*example\\.com/.*$"

void redirect(const char *target) {
    printf("Location: %s\n", target);
    printf("Content-Type: text/html\n\n");
    exit(0);
}

int main(int argc, char **argv) {
    const char *query = getenv("QUERY_STRING");
    if (query == NULL || strstr(query, "target=") != query) {
        redirect("/");
    }

    char target[256];
    sscanf(query, "target=%[^&]", target);

    regex_t regex;
    int reti;
    reti = regcomp(&regex, REGEX, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
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