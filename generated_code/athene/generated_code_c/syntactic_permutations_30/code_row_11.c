#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
    exit(0);
}

int main(int argc, char **argv) {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strstr(target, "target=") != target) {
        redirect("/");
    }

    char *query_value = strchr(target, '=');
    if (query_value == NULL) {
        redirect("/");
    }
    query_value++;

    regex_t regex;
    int reti;
    char msgbuf[100];

    const char *pattern = "^[a-zA-Z0-9]+(\\.[a-zA-Z0-9]*)*$";
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        printf("Regex compilation failed\n");
        exit(1);
    }

    reti = regexec(&regex, query_value, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        redirect(query_value);
    } else {
        redirect("/");
    }

    return 0;
}