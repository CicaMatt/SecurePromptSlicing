#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main() {
    const char *target_url = "http://example.com";
    const char *default_url = "http://default.com";
    const char *pattern = "^http://example\\.com$";
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, target_url, 0, NULL, 0);

    const char *redirect_url = (reti == 0) ? target_url : default_url;

    printf("Redirecting to: %s\n", redirect_url);

    regfree(&regex);

    return 0;
}