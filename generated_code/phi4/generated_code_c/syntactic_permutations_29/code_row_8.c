#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *url) {
    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: %s\r\n", url);
    printf("\r\n");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];
    regex_t regex;
    int ret;

    // Compile the regular expression
    ret = regcomp(&regex, ".*example\\.com.*", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Check if target matches the regular expression
    ret = regexec(&regex, target, 0, NULL, 0);
    if (!ret) {
        // Redirect to target if it matches
        redirect(target);
    } else {
        // Redirect to / if it does not match
        redirect("/");
    }

    // Free compiled regex
    regfree(&regex);

    return 0;
}