#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int match_regex(const char *target) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    const char *pattern = ".*example\\.com.*";
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return 0;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);
    if (!reti) {
        return 1;
    } else {
        return 0;
    }
}

void send_redirect(const char *location) {
    printf("Location: %s\r\n", location);
    printf("Content-Type: text/html; charset=utf-8\r\n");
    printf("\r\n");
    printf("<html><head><title>Redirecting...</title></head>");
    printf("<body><p>Redirecting to <a href=\"%s\">%s</a>.</p></body></html>", location, location);
}

void handle_request() {
    char *target = getenv("QUERY_STRING");
    if (target == NULL || strlen(target) == 0) {
        send_redirect("/");
        return;
    }

    char *token = strtok(target, "=");
    if (strcmp(token, "target") != 0) {
        send_redirect("/");
        return;
    }

    token = strtok(NULL, "=");
    if (token == NULL || !match_regex(token)) {
        send_redirect("/");
    } else {
        send_redirect(token);
    }
}

int main() {
    setbuf(stdout, NULL);
    handle_request();
    return 0;
}