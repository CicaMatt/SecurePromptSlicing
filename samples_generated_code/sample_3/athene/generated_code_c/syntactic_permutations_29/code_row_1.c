#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

void send_redirect(const char *location) {
    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: %s\r\n", location);
    printf("\r\n");
}

int main() {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strstr(target, "target=") != target) {
        send_redirect("/");
        return 0;
    }

    char *target_url = strchr(target, '=') + 1;
    if (strlen(target_url) == 0) {
        send_redirect("/");
        return 0;
    }

    regex_t regex;
    int reti;
    const char *pattern = "example\\.com";

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        send_redirect("/");
        return 0;
    }

    reti = regexec(&regex, target_url, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        send_redirect(target_url);
    } else {
        send_redirect("/");
    }

    return 0;
}