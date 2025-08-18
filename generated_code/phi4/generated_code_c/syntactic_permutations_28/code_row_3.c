#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "https://default.example.com"

int match_and_redirect(const char *target_url) {
    regex_t regex;
    int reti;
    const char *pattern = "^https?://(www\\.)?example\\.com/.*$";
    
    // Compile the regular expression
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Could not compile regex\n");
        return EXIT_FAILURE;
    }
    
    // Execute the regular expression
    reti = regexec(&regex, target_url, 0, NULL, 0);
    
    // Free memory allocated to the pattern buffer by regcomp()
    regfree(&regex);
    
    if (!reti) {
        printf("Redirecting to: %s\n", target_url);
        return EXIT_SUCCESS;
    } else if (reti == REG_NOMATCH) {
        printf("Redirecting to default URL: %s\n", DEFAULT_URL);
        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target_url = argv[1];
    match_and_redirect(target_url);

    return EXIT_SUCCESS;
}