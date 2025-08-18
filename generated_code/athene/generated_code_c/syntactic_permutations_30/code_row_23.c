#include <stdio.h>
#include <regex.h>
#include <string.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
}

int main() {
    const char *query = "target=abc-def.";
    const char *root = "/";
    regex_t regex;
    int reti;
    char *target = NULL;

    // Extract target from query
    if (strstr(query, "target=") != NULL) {
        char *eq_pos = strchr((char *)query, '=');
        eq_pos++;
        target = strdup(eq_pos);
    }

    if (target == NULL) {
        redirect(root);
        return 0;
    }

    // Compile regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Match target against regex
    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        redirect(target);
    } else {
        redirect(root);
    }

    regfree(&regex);
    free(target);

    return 0;
}