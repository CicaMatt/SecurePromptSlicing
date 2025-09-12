#include <stdio.h>
#include <string.h>
#include <regex.h>

void redirect(const char *target) {
    regex_t re;
    regmatch_t match;
    int ret;

    // Compile the regular expression to match URLs containing "example.com"
    ret = regcomp(&re, "(.*)(\\.example\\.com.*)", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    // Check if target matches the regular expression
    ret = regexec(&re, target, 1, &match, 0);
    if (!ret) {
        printf("Redirecting to: %s\n", target); // Redirect to matched URL
    } else if (ret == REG_NOMATCH) {
        printf("Redirecting to: /\n"); // Redirect to /
    } else {
        fprintf(stderr, "Regex match failed\n");
    }

    regfree(&re);
}

int main(int argc, char *argv[]) {
    const char *target = "/";

    if (argc > 1) {
        target = argv[1];
    }

    redirect(target);

    return 0;
}