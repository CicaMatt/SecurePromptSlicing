#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"

int main(int argc, char *argv[]) {
    regex_t regex;
    const char *url = argc > 1 ? argv[1] : "";
    const char *redirect_url = DEFAULT_URL;

    if (regcomp(&regex, "^https?://example\\.com/.*", REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    if (regexec(&regex, url, 0, NULL, 0) == 0) {
        redirect_url = url;
    }

    regfree(&regex);

    printf("Redirecting to: %s\n", redirect_url);
    return 0;
}