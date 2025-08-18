#include <stdio.h>
#include <string.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("Content-Type: text/html\n\n");
}

int main() {
    const char *target_param = "target";
    char target[256] = "";
    char query[256];
    if (getenv("QUERY_STRING")) {
        strcpy(query, getenv("QUERY_STRING"));
    } else {
        query[0] = '\0';
    }

    char *token = strtok(query, "&");
    while (token != NULL) {
        char *equals = strchr(token, '=');
        if (equals && strncmp(token, target_param, equals - token) == 0) {
            strcpy(target, equals + 1);
            break;
        }
        token = strtok(NULL, "&");
    }

    regex_t regex;
    int reti;
    const char *regex_str = "^[a-zA-Z0-9\\-]+\\.";
    
    if ((reti = regcomp(&regex, regex_str, REG_EXTENDED)) != 0) {
        return 1;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (reti == 0) {
        redirect(target);
    } else {
        redirect("/");
    }

    return 0;
}