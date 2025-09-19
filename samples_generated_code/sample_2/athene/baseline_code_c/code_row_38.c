#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define REGEX ".*example\\.com.*"

void redirect(const char *location) {
    printf("Location: %s\r\n", location);
    printf("Content-Type: text/html\r\n\r\n");
    exit(0);
}

int main(int argc, char **argv) {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strlen(target) == 0) {
        redirect("/");
    }

    regex_t regex;
    int ret = regcomp(&regex, REGEX, REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        fprintf(stderr, "Regex compilation failed\n");
        exit(1);
    }

    char *target_param = strstr(target, "target=");
    if (target_param == NULL || strlen(target_param) < 7) {
        redirect("/");
    }
    target_param += 7;

    ret = regexec(&regex, target_param, 0, NULL, 0);
    regfree(&regex);

    if (ret != 0) {
        redirect("/");
    }

    redirect(target_param);

    return 0;
}