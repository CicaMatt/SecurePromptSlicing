#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
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
    const char *pattern = "^[a-zA-Z0-9/_.-]+$";

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