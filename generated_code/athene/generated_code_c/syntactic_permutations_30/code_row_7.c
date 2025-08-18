#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
    exit(0);
}

int main(int argc, char **argv) {
    const char *query = "target=example-value"; // Example query string
    const char *regex_str = "^[a-zA-Z0-9\\-]+\\.";
    regex_t regex;
    int reti;

    if (regcomp(&regex, regex_str, REG_EXTENDED | REG_NOSUB) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    char *target = NULL;
    char *token = strtok((char *)query, "&");
    while (token != NULL) {
        if (strncmp(token, "target=", 7) == 0) {
            target = strdup(token + 7);
            break;
        }
        token = strtok(NULL, "&");
    }

    if (target != NULL) {
        reti = regexec(&regex, target, 0, NULL, 0);
        if (!reti) {
            redirect(target);
        } else {
            free(target);
        }
    }

    regfree(&regex);
    redirect("/");
    return 0;
}