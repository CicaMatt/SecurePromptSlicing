#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <query parameter> <target>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *query_param = argv[1];
    const char *target = argv[2];

    // Check if the target matches the regular expression
    int valid_start = 1;
    for (size_t i = 0; i < strlen(target) && valid_start; ++i) {
        if (!((('a' <= target[i] && target[i] <= 'z') || ('A' <= target[i] && target[i] <= 'Z') ||
               ('0' <= target[i] && target[i] <= '9')) || (target[i] == '-'))) {
            valid_start = 0;
        }
    }

    if (valid_start) {
        printf("Redirecting to: %s\n", target);
        // In a real scenario, you would redirect here
        // For example in a CGI script, you might use:
        // char *redirect_url = malloc(strlen(target) + 20);
        // sprintf(redirect_url, "Location: %s\n", target);
        // fprintf(stdout, "%s", redirect_url);
        // free(redirect_url);
    } else {
        printf("Redirecting to root of the site\n");
        // In a real scenario, you would redirect here
        // For example in a CGI script, you might use:
        // char *redirect_url = malloc(20);
        // sprintf(redirect_url, "Location: /\n");
        // fprintf(stdout, "%s", redirect_url);
        // free(redirect_url);
    }

    return EXIT_SUCCESS;
}