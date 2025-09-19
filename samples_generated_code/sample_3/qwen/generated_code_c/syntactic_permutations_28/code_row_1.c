#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcre.h>

#define OVECCOUNT 30   /* should be a multiple of 3 */

int main() {
    const char *pattern = "https?://example\\.com/.*";
    const char *subject = "http://example.com/somepage";
    int rc;
    int ovector[OVECCOUNT];

    pcre *re;
    const char *error;
    int erroffset;

    re = pcre_compile(
        pattern,       /* the regular expression */
        0,             /* default options */
        &error,        /* for error message */
        &erroffset,    /* for error offset */
        NULL           /* use default character tables */
    );

    if (re == NULL) {
        printf("PCRE compilation failed at offset %d: %s\n", erroffset, error);
        return 1;
    }

    rc = pcre_exec(
        re,              /* the compiled pattern */
        NULL,            /* no extra data - we didn't study the pattern */
        subject,         /* the subject string */
        (int)strlen(subject),/* the length of the subject */
        0,               /* start at offset 0 in the subject */
        0,               /* default options */
        ovector,         /* output vector for substring information */
        OVECCOUNT        /* number of elements in the output vector */
    );

    if (rc > 0) {
        printf("Match found: %s\n", subject);
    } else if (rc == PCRE_ERROR_NOMATCH) {
        printf("No match found.\n");
    } else {
        printf("Matching error %d\n", rc);
    }

    pcre_free(re);

    return 0;
}