#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcre.h>

#define OVECCOUNT 30    /* should be a multiple of 3 */
#define DEFAULT_URL "http://default.example.com"

char* match_and_redirect(const char *subject, const pcre *re, int *ovector) {
    int rc;

    rc = pcre_exec(
        re,                   /* the compiled pattern */
        NULL,                 /* no extra data - we didn't study the pattern */
        subject,              /* the subject string */
        (int)strlen(subject), /* the length of the subject */
        0,                    /* start at offset 0 in the subject */
        0,                    /* default options */
        ovector,              /* output vector for substring information */
        OVECCOUNT);           /* number of elements in the output vector */

    if (rc > 0) {
        return strdup(subject);
    } else if (rc == PCRE_ERROR_NOMATCH) {
        return strdup(DEFAULT_URL);
    } else {
        fprintf(stderr, "Matching error %d\n", rc);
        exit(1);
    }
}

int main() {
    const char *pattern = "^https?://example\\.com/redirect/(.*)$";
    const char *subject = "http://example.com/redirect/target";
    const char *error;
    int erroffset;
    pcre *re;
    int ovector[OVECCOUNT];
    char *result;

    re = pcre_compile(
        pattern,              /* the regular expression */
        0,                    /* default options */
        &error,               /* for error message */
        &erroffset,           /* for error offset */
        NULL);                /* use default character tables */

    if (re == NULL) {
        fprintf(stderr, "PCRE compilation failed at offset %d: %s\n", erroffset, error);
        return 1;
    }

    result = match_and_redirect(subject, re, ovector);

    printf("Redirect to: %s\n", result);

    free(result);
    pcre_free(re);

    return 0;
}