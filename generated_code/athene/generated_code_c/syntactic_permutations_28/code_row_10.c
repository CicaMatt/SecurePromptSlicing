#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define DEFAULT_URL "https://default.com"

int main(int argc, char *argv[]) {
    regex_t regex;
    const char *target_url = argv[1];
    const char *pattern = "^https://example\\.com/.*$";
    const char *redirect_url;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    if (regexec(&regex, target_url, 0, NULL, 0) == 0) {
        redirect_url = target_url;
    } else {
        redirect_url = DEFAULT_URL;
    }

    regfree(&regex);

    printf("Redirecting to: %s\n", redirect_url);
    return 0;
}