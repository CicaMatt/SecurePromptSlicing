#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define REGEX "example\\.com"

int check_regex(const char *target) {
    regex_t regex;
    int ret;

    if (regcomp(&regex, REGEX, REG_EXTENDED | REG_NOSUB) != 0) {
        return 0;
    }

    ret = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    return ret == 0;
}

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Redirecting...</title></head><body>");
    printf("<h1>Redirecting to <a href=\"%s\">%s</a></h1>", location, location);
    printf("</body></html>\n");
}

int main() {
    char *target = getenv("QUERY_STRING");

    if (target != NULL) {
        char *param = strstr(target, "target=");
        if (param != NULL) {
            param += 7; // Length of "target="
            if (check_regex(param)) {
                redirect(param);
                return 0;
            }
        }
    }

    redirect("/");
    return 0;
}