#include <stdio.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"

void redirect_url(const char *target_url, const char **redirect_url) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    if (regcomp(&regex, "^https?://example\\.com/.*", REG_EXTENDED|REG_NOSUB) != 0) {
        printf("Could not compile regex\n");
        *redirect_url = DEFAULT_URL;
        return;
    }

    reti = regexec(&regex, target_url, (size_t) 0, NULL, 0);
    if (reti == REG_NOMATCH) {
        *redirect_url = DEFAULT_URL;
    } else {
        *redirect_url = target_url;
    }

    regfree(&regex);
}

int main() {
    const char *target_url = "http://example.com/path";
    const char *redirect_url;

    redirect_url(target_url, &redirect_url);
    printf("Redirecting to: %s\n", redirect_url);

    return 0;
}