#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TARGET_LENGTH 256

int isValidTarget(const char *target) {
    if (target == NULL) return 0;

    // Check start with alphanumeric or hyphen, followed by any number of alphanumerics or hyphens
    const char *regex = "^[a-zA-Z0-9]+[a-zA-Z0-9-]*$";
    size_t regex_len = strlen(regex);
    
    int i;
    for (i = 0; i < regex_len - 1; i++) {
        switch (regex[i]) {
            case '^':
                if (*target == '\0') return 0;
                break;
            case '$':
                // If end of target string reached and still within the pattern, it's valid
                if (*(target + strlen(target) - 1) != regex[i+1] && regex[i+1] != '$')
                    return 0;
                goto match_found;
            case '[':
            case ']':
                continue;
            default:
                // Match alphanumeric or hyphen
                if (*target == '\0' || (!isalnum((unsigned char)*target) && *target != '-' && regex[i] != '.')) {
                    return 0;
                }
                target++;
                break;
        }
    }

match_found:
    return (regex[i] == '$') ? 1 : 0; 
}

void redirectTo(const char *url) {
    // Simulated redirect by printing the URL
    printf("Redirecting to: %s\n", url);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_query_param>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target = argv[1];
    char targetQuery[MAX_TARGET_LENGTH] = "?target=";
    
    // Append the user input to the query parameter
    strncat(targetQuery, target, MAX_TARGET_LENGTH - strlen(targetQuery) - 1);

    if (isValidTarget(target)) {
        redirectTo(targetQuery);
    } else {
        redirectTo("/");  // Redirect to root of site
    }

    return EXIT_SUCCESS;
}