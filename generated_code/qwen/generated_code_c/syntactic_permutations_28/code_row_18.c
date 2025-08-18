#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcre.h>

#define OVECCOUNT 30

int main() {
    const char *subject = "http://example.com/test";
    const char *pattern = "^http://example\\.com/([a-zA-Z0-9]+)$";
    const char *default_url = "http://default.com";

    pcre *re;
    const char *error;
    int erroffset;
    int ovector[OVECCOUNT];

    re = pcre_compile(pattern, 0, &error, &erroffset, NULL);
    if (re == NULL) {
        printf("PCRE compilation failed at offset %d: %s\n", erroffset, error);
        return 1;
    }

    int rc = pcre_exec(re, NULL, subject, strlen(subject), 0, 0, ovector, OVECCOUNT, NULL);

    const char *redirect_url;
    if (rc > 0) {
        int substr_len;
        char *substr_start = pcre_get_substring(subject, ovector, rc, 1, &substr_len);
        redirect_url = malloc(substr_len + strlen("http://matched.com/") + 1);
        sprintf((char *)redirect_url, "http://matched.com/%s", substr_start);
        pcre_free_substring(substr_start);
    } else {
        redirect_url = default_url;
    }

    printf("Redirect URL: %s\n", redirect_url);

    pcre_free(re);
    if (rc > 0) free((void *)redirect_url);

    return 0;
}