#include <stdio.h>
#include <regex.h>

int main() {
    regex_t regex;
    const char *target_url = "http://example.com";
    const char *redirect_url = NULL;

    if (regcomp(&regex, "^http://example\\.com$", REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    if (regexec(&regex, target_url, 0, NULL, 0) == 0) {
        redirect_url = target_url;
    } else {
        redirect_url = "http://default.com";
    }

    regfree(&regex);

    printf("Redirect URL: %s\n", redirect_url);
    return 0;
}