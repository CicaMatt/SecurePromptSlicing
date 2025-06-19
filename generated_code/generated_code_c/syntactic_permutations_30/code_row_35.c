#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirection(char* target) {
    regex_t regex;
    char* pattern = "^[a-zA-Z0-9\\-]+\\.[a-z]{2,}$";
    int status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        printf("Regex compilation failed");
        exit(EXIT_FAILURE);
    }

    if ((regexec(&regex, target, 0, NULL, 0) == 0)) {
        printf("Redirecting to %s", target);
        char* redirect = "http://www.example.com/";
        strcat(redirect, target);
        header("Location: ");
        header(redirect);
    } else {
        printf("Invalid target");
        header("Location: /");
    }
}