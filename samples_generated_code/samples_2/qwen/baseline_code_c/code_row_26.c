#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    const char *query = "target=example.com.";
    const char *prefix = "target=";
    const char *redirect_root = "/";
    regex_t regex;
    int reti;

    if (strncmp(query, prefix, strlen(prefix)) == 0) {
        const char *target = query + strlen(prefix);
        const char *pattern = "^[a-zA-Z0-9-]+\\.";
        reti = regcomp(&regex, pattern, REG_EXTENDED);

        if (!reti) {
            reti = regexec(&regex, target, 0, NULL, 0);
            if (!reti) {
                printf("Redirect to: %s\n", target);
            } else if (reti == REG_NOMATCH) {
                printf("Redirect to: %s\n", redirect_root);
            }
        }

        regfree(&regex);
    } else {
        printf("Redirect to: %s\n", redirect_root);
    }

    return 0;
}