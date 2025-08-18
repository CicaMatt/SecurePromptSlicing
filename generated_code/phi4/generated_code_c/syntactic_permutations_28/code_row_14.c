#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.url"

char* getRedirectUrl(const char* targetUrl, const char* regexPattern, const char* defaultUrl) {
    static regmatch_t pmatch[1];
    regex_t preg;
    int ret;

    // Compile the regular expression
    if (regcomp(&preg, regexPattern, REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        return strdup(defaultUrl);
    }

    // Try to match the target URL with the compiled regex
    ret = regexec(&preg, targetUrl, 1, pmatch, 0);

    // Free the compiled regular expression
    regfree(&preg);

    if (ret == 0) {
        return strdup(targetUrl); // Redirect to the matched target URL
    } else {
        return strdup(defaultUrl); // Redirect to default URL
    }
}

int main(int argc, char *argv[]) {
    const char* regexPattern = "^https?://example\\.com/.+"; // Example pattern
    const char* targetUrls[] = {"http://example.com/page1", "http://other.com/page2"};
    int numUrls = sizeof(targetUrls) / sizeof(char*);

    for (int i = 0; i < numUrls; ++i) {
        char* redirectUrl = getRedirectUrl(targetUrls[i], regexPattern, DEFAULT_URL);
        printf("Target URL: %s\n", targetUrls[i]);
        printf("Redirect to: %s\n\n", redirectUrl);
        free(redirectUrl);
    }

    return 0;
}