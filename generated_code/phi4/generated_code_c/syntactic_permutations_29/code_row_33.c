#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 1024

int matches_regex(const char *str, const char *pattern) {
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        return 0; // Compilation failed
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    return !reti;
}

const char* redirect(const char *target) {
    const char *pattern = ".*example\\.com.*";
    
    if (matches_regex(target, pattern)) {
        return target;
    } else {
        return "/";
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *redirect_target = redirect(argv[1]);

    printf("Redirecting to: %s\n", redirect_target);

    // Simulate a web server redirection (for demonstration purposes)
    // In an actual web server, you would use something like `send_redirect(redirect_target);`
    printf("HTTP/1.1 302 Found\nLocation: %s\n\n", redirect_target);

    return EXIT_SUCCESS;
}
