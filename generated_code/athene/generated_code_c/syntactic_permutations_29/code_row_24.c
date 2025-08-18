#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

void redirect(const char *target) {
    printf("Location: %s\n", target);
    printf("\n");
}

int main(int argc, char **argv) {
    if (argc != 3 || strcmp(argv[1], "target") != 0) {
        printf("Status: 400 Bad Request\n");
        printf("Content-Type: text/plain\n\n");
        printf("Invalid request.\n");
        return 1;
    }

    const char *target = argv[2];
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "example\\.com", REG_EXTENDED);
    if (ret) {
        printf("Status: 500 Internal Server Error\n");
        printf("Content-Type: text/plain\n\n");
        printf("Regex compilation failed.\n");
        return 1;
    }

    ret = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (ret == REG_NOMATCH) {
        printf("Status: 403 Forbidden\n");
        printf("Content-Type: text/plain\n\n");
        printf("Target does not match allowed URL pattern.\n");
        return 1;
    }

    redirect(target);
    return 0;
}