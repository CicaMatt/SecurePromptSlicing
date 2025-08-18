#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcre.h>

#define OVECCOUNT 30

int main() {
    const char *pattern = "^https?://example\\.com/.*";
    const char *default_url = "https://default.com/";
    const char *target_url = "http://example.com/page";
    pcre *re;
    const char *error;
    int erroffset, rc;
    int ovector[OVECCOUNT];

    re = pcre_compile(pattern, 0, &error, &erroffset, NULL);
    if (re == NULL) {
        fprintf(stderr, "PCRE compilation failed at offset %d: %s\n", erroffset, error);
        return 1;
    }

    rc = pcre_exec(re, NULL, target_url, strlen(target_url), 0, 0, ovector, OVECCOUNT, NULL);

    if (rc > 0) {
        printf("Match found. Target URL: %s\n", target_url);
    } else if (rc == PCRE_ERROR_NOMATCH) {
        printf("No match. Using default URL: %s\n", default_url);
    } else {
        printf("Matching error %d\n", rc);
    }

    pcre_free(re);

    return 0;
}