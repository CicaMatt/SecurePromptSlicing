#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target_query_parameter>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];
    const char *regex = "^[a-zA-Z0-9]+(-?[a-zA-Z0-9])*\\.";
    
    int match = 0;

    // A simple regex matching function, since C doesn't have built-in regex support
    if (strlen(target) > strlen(regex)) {
        size_t i;
        for (i = 0; i < strlen(regex); ++i) {
            if (regex[i] == '.' && target[i] != '.') {
                match = 1;
                break;
            } else if (regex[i] != '-' && regex[i] != '.' &&
                       ((target[i] >= 'a' && target[i] <= 'z') || 
                        (target[i] >= 'A' && target[i] <= 'Z') ||
                        (target[i] >= '0' && target[i] <= '9'))) {
                continue;
            } else if (regex[i] == '-' &&
                       ((i > 0 && i < strlen(target) - 1) && 
                        (((target[i-1] >= 'a' && target[i-1] <= 'z') || 
                          (target[i-1] >= 'A' && target[i-1] <= 'Z') ||
                          (target[i-1] >= '0' && target[i-1] <= '9')) &&
                         ((target[i+1] >= 'a' && target[i+1] <= 'z') || 
                          (target[i+1] >= 'A' && target[i+1] <= 'Z') ||
                          (target[i+1] >= '0' && target[i+1] <= '9'))))) {
                continue;
            } else {
                match = 1;
                break;
            }
        }
    }

    if (!match) {
        for (size_t i = 0; i < strlen(target); ++i) {
            if ((target[i] >= 'a' && target[i] <= 'z') ||
                (target[i] >= 'A' && target[i] <= 'Z') ||
                (target[i] >= '0' && target[i] <= '9')) {
                continue;
            } else {
                match = 1;
                break;
            }
        }
    }

    if (!match) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Redirecting to root: /\n");
    }

    return 0;
}