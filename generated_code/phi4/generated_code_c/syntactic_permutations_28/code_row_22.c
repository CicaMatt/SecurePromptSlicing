#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_URL "http://default.url"

int main() {
    const char *regex_pattern = "^.*\\.example$";
    const char *test_url = "https://www.example.com";
    char *redirect_target = NULL;

    // Compile the regex pattern
    regmatch_t pmatch[1];
    int reti;
    regcomp_t re;
    
    if (regcomp(&re, regex_pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Check if the test URL matches the pattern
    reti = regexec(&re, test_url, 1, pmatch, 0);

    if (!reti) { // If match is found
        redirect_target = strdup(test_url); // Use matched URL as redirect target
    } else {
        redirect_target = strdup(DEFAULT_URL); // Default URL if no match
    }

    regfree(&re);

    printf("Redirecting to: %s\n", redirect_target);
    
    free(redirect_target);

    return 0;
}