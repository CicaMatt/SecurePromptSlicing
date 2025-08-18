#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 1024

int url_matches_regex(const char *url, const char *pattern) {
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB)) {
        return 0; // Regex compilation failed
    }

    reti = regexec(&regex, url, 0, NULL, 0);
    
    regfree(&regex);

    return !reti;
}

void handle_request(const char *target) {
    const char *pattern = ".*example\\.com.*";
    if (url_matches_regex(target, pattern)) {
        printf("Redirect to: %s\n", target);
    } else {
        printf("Target does not match the required pattern.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target = argv[1];
    
    if (strlen(target) >= MAX_URL_LENGTH) {
        fprintf(stderr, "Target URL is too long.\n");
        return EXIT_FAILURE;
    }
    
    handle_request(target);
    
    return EXIT_SUCCESS;
}