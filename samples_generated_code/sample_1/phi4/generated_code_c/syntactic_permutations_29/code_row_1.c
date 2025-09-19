#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *target) {
    const char *pattern = ".*example\\.com.*";
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        printf("Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, target, 0, NULL, 0);

    if (!reti) {
        printf("Redirecting to: %s\n", target);
        // In a real application, you'd use an actual redirect function here
    } else {
        printf("Redirecting to: /\n");
        // In a real application, you'd use an actual redirect function here
    }

    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_url>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];
    redirect(target);

    return 0;
}