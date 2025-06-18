#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    char *default_url = "https://www.example.com";
    const char *target_url = "/path/to/file";
    regex_t reg;
    int ret;

    // Compile regular expression once at startup
    ret = regcomp(&reg, "^/path/to/file$", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    // Match target URL against regular expression
    ret = regexec(&reg, target_url, 0, NULL, 0);
    if (!ret) {
        printf("Matched: %s\n", target_url);
    } else if (ret == REG_NOMATCH) {
        printf("No match: %s\n", default_url);
    } else {
        char msgbuf[100];
        regerror(ret, &reg, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return EXIT_FAILURE;
    }

    // Clean up
    regfree(&reg);
    return EXIT_SUCCESS;
}