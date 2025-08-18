#include <stdio.h>
#include <string.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    const char *query = "param=value&target=http://example.com/path";
    const char *pattern = "^([a-zA-Z0-9]+(-[a-zA-Z0-9]+)*\\.)";

    regex_t regex;
    regmatch_t match;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        redirect("/");
        return 1;
    }

    const char *target_start = strstr(query, "target=");
    if (!target_start) {
        redirect("/");
        return 1;
    }
    
    target_start += strlen("target=");

    // Check if the string after "target=" matches the regex
    if (regexec(&regex, target_start, 1, &match, 0) == 0 && match.rm_so == 0) {
        redirect(target_start);
    } else {
        redirect("/");
    }

    regfree(&regex);
    return 0;
}