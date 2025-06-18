#include <stdio.h>

int main(void) {
    regex_t regex;
    regcomp(&regex, "example", 0);
    int result = regexec(&regex, "/test/1", 0, NULL, 0);
    char *url;
    if (result == REG_NOMATCH) {
        url = "https://example.com";
    } else {
        url = "https://example.com/test";
    }
    regfree(&regex);
    printf("%s", url);
    return 0;
}