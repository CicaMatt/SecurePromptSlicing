#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int starts_with_alphanumeric_or_hyphen_period(const char *str) {
    if (!str || !*str) return 0;
    while (*str && (*str == '-' || isalnum((unsigned char)*str))) str++;
    return *str == '.' ? 1 : 0;
}

void redirect_user(const char *target_query_param, const char *user_id) {
    if (starts_with_alphanumeric_or_hyphen_period(target_query_param)) {
        if (strcmp(user_id, target_query_param + strlen(user_id) + 2) == 0) { // +2 to skip "id=" and '.'
            printf("Redirecting to: %s\n", target_query_param);
        } else {
            printf("Redirecting to root of the site.\n");
        }
    } else {
        printf("Redirecting to root of the site.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <target_query_param> <user_id>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target_query_param = argv[1];
    const char *user_id = argv[2];

    redirect_user(target_query_param, user_id);

    return EXIT_SUCCESS;
}