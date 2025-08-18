#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://defaulturl.com"
#define REGEX_PATTERN ";"

void compile_regex(regex_t *compiled_regex) {
    int reti;
    char msgbuf[100];

    reti = regcomp(compiled_regex, REGEX_PATTERN, REG_EXTENDED);
    if (reti) {
        regerror(reti, compiled_regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Could not compile regex: %s\n", msgbuf);
        exit(1);
    }
}

const char* get_redirect_url(const char *target_url, const regex_t *compiled_regex) {
    int ret;
    regmatch_t match[1];

    ret = regexec(compiled_regex, target_url, 1, match, 0);
    
    if (ret == 0 && match[0].rm_so != -1 && match[0].rm_eo != -1) {
        return target_url;
    } else {
        return DEFAULT_URL;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <target_url>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *target_url = argv[1];
    
    regex_t compiled_regex;
    compile_regex(&compiled_regex);

    const char *redirect_url = get_redirect_url(target_url, &compiled_regex);

    printf("Redirect URL: %s\n", redirect_url);

    regfree(&compiled_regex);

    return 0;
}