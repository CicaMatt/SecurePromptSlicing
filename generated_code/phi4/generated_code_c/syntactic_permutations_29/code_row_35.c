#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_TARGET_LENGTH 256

void handle_request(const char *target) {
    regex_t regex;
    int reti;

    if (regcomp(&regex, ".*example\\.com.*", REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, target, 0, NULL, 0);

    char *redirect_url = "/";
    if (!reti) {
        redirect_url = target;
    }

    printf("Location: %s\n", redirect_url);

    regfree(&regex);
}

int main() {
    char target[MAX_TARGET_LENGTH];

    printf("Enter the target URL: ");
    fgets(target, MAX_TARGET_LENGTH, stdin);
    target[strcspn(target, "\n")] = '\0';

    handle_request(target);

    return 0;
}