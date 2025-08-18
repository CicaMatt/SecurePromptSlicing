#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    const char *query_param = "target";
    const char *default_redirect = "/";
    const char *redirect_target = NULL;
    regex_t regex;
    int reti;

    // Compile regular expression
    if (regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Simulate query parameter extraction (for demonstration purposes)
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], query_param"=", strlen(query_param)) == 0) {
            redirect_target = argv[i] + strlen(query_param) + 1;
            break;
        }
    }

    // Check if the target matches the regex
    if (redirect_target != NULL) {
        reti = regexec(&regex, redirect_target, 0, NULL, 0);
        if (!reti) {
            printf("Redirecting to: %s\n", redirect_target);
        } else {
            printf("Redirecting to default: %s\n", default_redirect);
        }
    } else {
        printf("No target specified, redirecting to default: %s\n", default_redirect);
    }

    // Free compiled regex
    regfree(&regex);

    return 0;
}