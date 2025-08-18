#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define REGEX_PATTERN "example\\.com"

void redirect(const char *target) {
    printf("Location: %s\n", target);
    printf("\n");
    exit(0);
}

int main(int argc, char **argv) {
    if (argc != 3 || strcmp(argv[1], "/redirect") != 0) {
        return 0;
    }

    const char *target = argv[2];
    regex_t regex;
    int ret = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED);
    if (ret) {
        return 1;
    }

    ret = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        redirect(target);
    } else {
        redirect("/");
    }

    return 0;
}