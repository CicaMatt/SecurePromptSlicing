#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_query_parameter>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target = argv[1];
    
    regex_t regex;
    int ret;

    // Compile regular expression
    ret = regcomp(&regex, "^[a-zA-Z0-9-]+\\.$", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    // Execute regular expression
    ret = regexec(&regex, target, 0, NULL, 0);

    // Free compiled regular expression
    regfree(&regex);

    if (!ret) {
        redirect(target);
    } else if (ret == REG_NOMATCH) {
        redirect("/");
    } else {
        fprintf(stderr, "Regex match failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}