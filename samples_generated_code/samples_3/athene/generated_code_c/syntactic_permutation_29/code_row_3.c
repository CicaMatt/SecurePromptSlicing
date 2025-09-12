#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define REGEX_PATTERN "example\\.com"

void redirect(const char *target) {
    printf("Location: %s\n", target);
    printf("\n");
    exit(0);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("HTTP/1.1 400 Bad Request\n");
        return 1;
    }

    const char *target = argv[1];
    regex_t regex;
    int ret;

    ret = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED);
    if (ret) {
        printf("HTTP/1.1 500 Internal Server Error\n");
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