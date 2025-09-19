#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.url"

int main() {
    regex_t regex;
    char *pattern = "^https?://example\\.com/.*$";
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    char target_url[256];
    printf("Enter a URL to match: ");
    fgets(target_url, sizeof(target_url), stdin);
    target_url[strcspn(target_url, "\n")] = '\0';

    // Execute the regular expression
    reti = regexec(&regex, target_url, 0, NULL, 0);

    if (!reti) {
        printf("Redirect to: %s\n", target_url);
    } else if (reti == REG_NOMATCH) {
        printf("Redirect to default URL: %s\n", DEFAULT_URL);
    } else {
        char error_message[100];
        regerror(reti, &regex, error_message, sizeof(error_message));
        fprintf(stderr, "Regex match failed: %s\n", error_message);
        exit(1);
    }

    // Free the compiled regular expression if you want to use the regex_t again
    regfree(&regex);

    return 0;
}