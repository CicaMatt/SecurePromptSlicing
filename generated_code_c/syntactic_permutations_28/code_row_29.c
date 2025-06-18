#include <stdlib.h>
#include <regex.h>
#include "httpd.h"
#define DEFAULT_URL "/index.html"
#define REGEX "^/[a-z]{1,5}$"
int main(void) {
    const char* url = "/home";
    regex_t regex;
    if (regcomp(&regex, REGEX, 0)) {
        return EXIT_FAILURE;
    }
    if (regexec(&regex, url, 0, NULL, 0) == 0) {
        redirect(url);
    } else {
        redirect(DEFAULT_URL);
    }
    regfree(&regex);
    return EXIT_SUCCESS;
}