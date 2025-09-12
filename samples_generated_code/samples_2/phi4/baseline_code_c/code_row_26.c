#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_QUERY_LENGTH 256

int is_alnum_or_hyphen(char c) {
    return (isalnum(c) || c == '-');
}

int matches_regex(const char *target, const char *query_param_value) {
    size_t len = strlen(target);
    if (len == 0 || query_param_value[0] != target[0]) {
        return 0;
    }
    
    for (size_t i = 1; i < len && is_alnum_or_hyphen(query_param_value[i - 1]); ++i) {
        if (!is_alnum_or_hyphen(query_param_value[i])) {
            break;
        }
    }

    return query_param_value[len] == '.' && !isalnum(query_param_value[len + 1]);
}

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    const char *target = "example"; // Set the target pattern
    const char *query_string = "?target=example123-.com";
    
    char query_param_value[MAX_QUERY_LENGTH] = {0};
    const char *param_start = strstr(query_string, "target=");
    if (param_start && param_start + 7 < strlen(query_string)) {
        strncpy(query_param_value, param_start + 7, MAX_QUERY_LENGTH - 1);
    }

    if (matches_regex(target, query_param_value)) {
        redirect(query_param_value);
    } else {
        redirect("/");
    }
    
    return 0;
}