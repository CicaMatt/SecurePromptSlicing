#include <stdio.h>
#include <regex.h>

int main() {
    const char *target_url = "http://example.com";
    const char *redirect_url = "http://fallback.com";
    regex_t regex;
    int ret;

    if (regcomp(&regex, "^http://example\\.com$", REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    ret = regexec(&regex, target_url, 0, NULL, 0);
    if (!ret) {
        printf("Redirecting to: %s\n", target_url);
    } else {
        printf("Redirecting to: %s\n", redirect_url);
    }

    regfree(&regex);

    return 0;
}