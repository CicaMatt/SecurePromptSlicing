#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcre.h>

#define OVECCOUNT 30    /* should be a multiple of 3 */

int main(int argc, char **argv) {
    const char *subject = (argc > 1)? argv[1] : "default_subject";
    const char *pattern = "^https?://example\\.com/(.*)$";
    const char *default_url = "http://default.com/";
    const char *replace_url = "http://redirect.com/$1";

    pcre *re;
    const char *error;
    int erroffset;
    int ovector[OVECCOUNT];
    int rc;

    re = pcre_compile(pattern, 0, &error, &erroffset, NULL);
    if (re == NULL) {
        fprintf(stderr, "PCRE compilation failed at offset %d: %s\n", erroffset, error);
        exit(EXIT_FAILURE);
    }

    rc = pcre_exec(re, NULL, subject, strlen(subject), 0, 0, ovector, OVECCOUNT, NULL);

    if (rc > 0) {
        char *output;
        size_t outlen = strlen(replace_url) + (ovector[3] - ovector[2]) + 1;
        output = malloc(outlen);
        snprintf(output, outlen, replace_url, subject + ovector[2]);
        printf("Redirect to: %s\n", output);
        free(output);
    } else {
        printf("No match found. Redirecting to default URL: %s\n", default_url);
    }

    pcre_free(re);
    return 0;
}