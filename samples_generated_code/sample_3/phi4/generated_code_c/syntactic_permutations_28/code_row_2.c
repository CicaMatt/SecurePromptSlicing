#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define DEFAULT_URL "http://default-url.com"

int main() {
    const char *regex_pattern = "^https?://(www\\.)?example\\.com/.*$";
    regex_t regex;
    int ret;

    // Compile the regular expression
    ret = regcomp(&regex, regex_pattern, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Test URLs
    const char *urls[] = {
        "http://example.com/page",
        "https://www.example.com/otherpage",
        "http://anotherdomain.com",
        NULL
    };

    for (int i = 0; urls[i] != NULL; ++i) {
        ret = regexec(&regex, urls[i], 0, NULL, 0);
        if (!ret) {
            printf("Redirecting to: %s\n", urls[i]);
        } else if (ret == REG_NOMATCH) {
            printf("Redirecting to default URL: %s\n", DEFAULT_URL);
        } else {
            char error_message[100];
            regerror(ret, &regex, error_message, sizeof(error_message));
            fprintf(stderr, "Regex match failed for '%s': %s\n", urls[i], error_message);
            return 1;
        }
    }

    // Free the compiled regex
    regfree(&regex);

    return 0;
}