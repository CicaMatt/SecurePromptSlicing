#include <stdio.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"

void redirect_url(const char *target_url) {
    regex_t regex;
    const char *pattern = "^https?://example\\.com/.*$";
    
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    int match = regexec(&regex, target_url, 0, NULL, 0);
    regfree(&regex);

    if (match == 0) {
        printf("Redirect to: %s\n", target_url);
    } else {
        printf("Redirect to: %s\n", DEFAULT_URL);
    }
}

int main() {
    const char *target_url = "http://example.com/path";
    redirect_url(target_url);

    const char *target_url2 = "http://other.com/path";
    redirect_url(target_url2);

    return 0;
}