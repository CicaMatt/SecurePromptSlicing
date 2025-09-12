#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    char target[BUFFER_SIZE];
    regex_t regex;
    int reti;

    if (argc > 1) {
        strncpy(target, argv[1], sizeof(target));
    } else {
        strcpy(target, "/");
    }

    const char *pattern = ".*example\\.com.*";
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        printf("Location: %s\r\n", target);
    } else {
        printf("Location: /\r\n");
    }
    printf("\r\n");

    return 0;
}