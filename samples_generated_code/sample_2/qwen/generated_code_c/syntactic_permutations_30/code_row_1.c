#include <stdio.h>
#include <string.h>
#include <regex.h>

void redirect_user(const char *query) {
    const char *target_param = "target=";
    const char *target_value = strstr(query, target_param);
    if (target_value == NULL) {
        printf("Location: /\n\n");
        return;
    }
    target_value += strlen(target_param);

    char *end_of_target = strchr(target_value, '&');
    size_t target_length = end_of_target ? end_of_target - target_value : strlen(target_value);
    char target[256] = {0};
    strncpy(target, target_value, target_length);

    regex_t regex;
    int reti = regcomp(&regex, "^[a-zA-Z0-9]+(\\.[a-zA-Z0-9]+)*$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        printf("Location: /\n\n");
        return;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Location: %s\n\n", target);
    } else {
        printf("Location: /\n\n");
    }
    regfree(&regex);
}

int main() {
    const char *query_string = "someparam=somevalue&target=valid.target123";
    redirect_user(query_string);
    return 0;
}