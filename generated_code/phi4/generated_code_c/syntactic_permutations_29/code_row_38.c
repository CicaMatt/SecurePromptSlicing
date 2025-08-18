#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define TARGET_SIZE 256

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target>\n", argv[0]);
        return 1;
    }

    const char *pattern = "^.*example\\.com$";
    regex_t regex;
    regmatch_t pmatch;

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        printf("Could not compile regular expression.\n");
        return 1;
    }

    char *target = argv[1];
    int match = regexec(&regex, target, 0, NULL, 0);

    if (match == 0) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Target does not match. Redirecting to /\n");
    }

    regfree(&regex);
    return 0;
}