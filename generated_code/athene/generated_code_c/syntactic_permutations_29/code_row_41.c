#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

int check_url(const char *url) {
    regex_t regex;
    int reti;
    const char *pattern = "https?://[a-zA-Z0-9.-]+(\\/[a-zA-Z0-9.?=#&%-]*)?$";

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return 0;
    }

    reti = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    return reti == 0;
}

void redirect(const char *target) {
    printf("Location: %s\n", target);
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Redirecting...</title></head><body>");
    printf("<h1>Redirecting to <a href=\"%s\">%s</a></h1>", target, target);
    printf("</body></html>\n");
}

int main() {
    char *target = getenv("QUERY_STRING");
    if (target == NULL || strlen(target) > MAX_URL_LENGTH) {
        redirect("/");
        return 0;
    }

    if (check_url(target)) {
        redirect(target);
    } else {
        redirect("/");
    }

    return 0;
}