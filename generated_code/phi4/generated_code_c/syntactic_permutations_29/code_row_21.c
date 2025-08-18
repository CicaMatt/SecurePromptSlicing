#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *target) {
    const char *pattern = ".*example\\.com.*";
    regex_t regex;
    int reti;

    regcomp(&regex, pattern, REG_EXTENDED);
    reti = regexec(&regex, target, 0, NULL, 0);

    if (!reti) {
        printf("Location: %s\n", target);
    } else {
        printf("Location: /\n");
    }

    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    redirect(argv[1]);

    return EXIT_SUCCESS;
}