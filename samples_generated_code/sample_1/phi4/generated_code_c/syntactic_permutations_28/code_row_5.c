#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.url"

void handle_redirect(const char *target_url) {
    regex_t regex;
    int reti;

    // Compile regex once when the module is loaded
    if (regcomp(&regex, "^https?://.*", REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Check if target URL matches the pattern
    reti = regexec(&regex, target_url, 0, NULL, 0);
    if (!reti) {
        printf("Redirecting to: %s\n", target_url);
    } else {
        printf("Using default URL: %s\n", DEFAULT_URL);
        // Optionally redirect using the default URL
        // (In real application, you would perform a system call or use a library function here)
    }

    // Free compiled regular expression if you want to reuse it later
    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <target_url>\n", argv[0]);
        return 1;
    }

    handle_redirect(argv[1]);

    return 0;
}