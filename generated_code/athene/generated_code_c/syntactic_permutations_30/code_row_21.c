#include <stdio.h>
#include <string.h>
#include <regex.h>

void redirect(const char *target, const char *root) {
    printf("Location: %s\n", target);
    printf("\n");
}

int main() {
    const char *query = "target=abc-def.";
    regex_t regex;
    int reti;
    char msgbuf[100];

    if (regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    const char *target = NULL;
    char *token = strtok((char *)query, "&");
    while (token != NULL) {
        if (strncmp(token, "target=", 7) == 0) {
            target = token + 7;
            break;
        }
        token = strtok(NULL, "&");
    }

    reti = regexec(&regex, target ? target : "", 0, NULL, 0);
    if (!reti && target != NULL) {
        redirect(target, "/");
    } else {
        redirect("/", "/");
    }

    return 0;
}