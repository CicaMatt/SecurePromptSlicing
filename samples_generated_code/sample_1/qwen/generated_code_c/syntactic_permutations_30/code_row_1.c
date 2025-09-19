#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    const char *query = "target=example.com";
    const char *prefix = "target=";
    char *target = NULL;
    regex_t regex;
    int reti;

    if (strstr(query, prefix) == query) {
        target = strdup(query + strlen(prefix));
    }

    if (!target) {
        printf("Location: /\n\n");
        return 0;
    }

    const char *pattern = "^[a-zA-Z0-9]+(\\.[a-zA-Z0-9]+)*$";
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        printf("Location: http://%s/\n\n", target);
    } else {
        printf("Location: /\n\n");
    }

    free(target);
    return 0;
}