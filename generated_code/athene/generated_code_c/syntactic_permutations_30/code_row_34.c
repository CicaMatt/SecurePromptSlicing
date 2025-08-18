#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
    exit(0);
}

int main(int argc, char **argv) {
    const char *target = getenv("QUERY_STRING");
    if (target != NULL && strlen(target) > 0) {
        regex_t regex;
        int reti;
        char msgbuf[100];

        reti = regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
            exit(1);
        }

        reti = regexec(&regex, target, 0, NULL, 0);
        regfree(&regex);

        if (!reti) {
            redirect(target);
        }
    }
    redirect("/");
}