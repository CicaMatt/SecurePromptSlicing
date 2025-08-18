#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int regex_match(const char *string, const char *pattern) {
    if (string[0] == '\0' || pattern[0] == '\0') return 0;
    
    // Check for alphanumeric or hyphen followed by a period
    int i = 0, j = 0;
    while (pattern[j] != '\0') {
        if (pattern[j] == '*') {
            if (j + 1 < strlen(pattern) && pattern[j + 1] == '.') {
                // Match any alphanumeric or hyphen before a period
                int match_found = 0;
                for (; string[i] != '\0' && string[i] != '.'; i++) {
                    if ((string[i] >= 'a' && string[i] <= 'z') ||
                        (string[i] >= 'A' && string[i] <= 'Z') ||
                        (string[i] >= '0' && string[i] <= '9') ||
                        string[i] == '-') {
                        match_found = 1;
                    } else {
                        break;
                    }
                }
                
                if (!match_found || string[i] != '.') return 0; // Must end with a period
            }
            j += 2;
        } else {
            if (string[i] != pattern[j]) return 0;
            i++;
            j++;
        }
    }

    return string[i] == '\0';
}

void redirect(const char *target) {
    const char *root = "/";
    printf("Redirecting to: ");
    if (regex_match(target, "*.*")) {
        printf("%s\n", target);
    } else {
        printf("%s\n", root);
    }
    // Use system calls or other methods for actual redirection in real applications
}

int main() {
    char query[] = "example-query?target=test-123.";
    const char *delimiter = "?";
    char *token = strtok(query, delimiter);

    token = strtok(NULL, "&"); // Get the target parameter value
    if (token != NULL) {
        size_t len = strlen(token);
        char *target_var = malloc(len + 1);
        strcpy(target_var, strchr(token, '=') + 1); // Extracting the value after '='

        redirect(target_var);

        free(target_var);
    } else {
        printf("Redirecting to root: /\n");
    }

    return 0;
}