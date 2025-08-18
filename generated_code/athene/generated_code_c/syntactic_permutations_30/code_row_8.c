#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("Content-Type: text/html\n\n");
    exit(0);
}

int main(int argc, char **argv) {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strchr(target, '=') == NULL) {
        redirect("/");
    }

    char *value = strchr(target, '=') + 1;
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^-+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    reti = regexec(&regex, value, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        redirect(value);
    } else {
        redirect("/");
    }

    return 0;
}