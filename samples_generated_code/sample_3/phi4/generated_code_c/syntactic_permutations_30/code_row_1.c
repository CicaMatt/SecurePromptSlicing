#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_alphanumeric_or_period(const char *str) {
    while (*str != '\0') {
        if (!isalnum((unsigned char)*str) && *str != '.') {
            return 0;
        }
        str++;
    }
    return 1;
}

void redirect_user(const char *url) {
    printf("Redirecting to: %s\n", url);
    // In a real application, you would use something like
    // `system("open " + url)` on macOS or equivalent in other systems
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <target_query_param> <query_string>\n", argv[0]);
        return 1;
    }

    const char *target_query_param = argv[1];
    const char *query_string = argv[2];

    // Extract the value of the target query parameter
    const char *prefix = "target=";
    char *start_ptr = strstr(query_string, prefix);
    
    if (!start_ptr) {
        printf("No target parameter found.\n");
        redirect_user("/");
        return 0;
    }

    start_ptr += strlen(prefix); // Move past the 'target=' part
    const char *end_ptr = strchr(start_ptr, '&');
    const char *url_end_ptr = end_ptr ? end_ptr : start_ptr + strlen(start_ptr);

    size_t target_length = url_end_ptr - start_ptr;
    char target[target_length + 1];
    strncpy(target, start_ptr, target_length);
    target[target_length] = '\0';

    if (is_alphanumeric_or_period(target)) {
        redirect_user(target);
    } else {
        redirect_user("/");
    }

    return 0;
}