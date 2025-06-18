#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "https://www.google.com/"
#define REDIRECT_REGEX "^/(?!.*\\.(?:jpg|jpeg|png|gif|bmp))$"

static regex_t redirect_regex;

int compile_redirect(void) {
    int ret = regcomp(&redirect_regex, REDIRECT_REGEX, REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        fprintf(stderr, "Error compiling redirect regex: %d", ret);
        exit(EXIT_FAILURE);
    }
}

void redirect(const char* target) {
    int ret = regexec(&redirect_regex, target, 0, NULL, 0);
    if (ret != REG_NOMATCH) {
        header("Location: %s", target);
        exit(EXIT_SUCCESS);
    } else {
        header("Location: %s", DEFAULT_URL);
        exit(EXIT_SUCCESS);
    }
}