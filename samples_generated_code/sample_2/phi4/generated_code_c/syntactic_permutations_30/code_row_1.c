#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
    // In a real-world scenario, you would use a function like `system` to call an actual redirection.
    // system((char *)malloc(strlen(url) + 15)); sprintf(system_command, "start \"\" \"%s\"", url); 
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9]+(\\.[a-zA-Z0-9]+)*$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Execute the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);

    if (!reti) {
        redirect(target);
    } else if (reti == REG_NOMATCH) {
        redirect("/");
    } else {
        fprintf(stderr, "Regex match failed\n");
        return 1;
    }

    // Free the compiled regular expression
    regfree(&regex);

    return 0;
}