#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <url> <target>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    const char *targetParamStr = argv[2];

    // Extract the target value from "target=<value>" string
    char *equalSignPos = strchr(targetParamStr, '=');
    if (equalSignPos == NULL) {
        printf("Invalid target parameter\n");
        return 1;
    }
    
    const char *targetValueStr = equalSignPos + 1;

    // Check if the target value matches the regular expression
    int isMatch = 1; // assume it's a match initially

    for (const char *p = targetValueStr; *p != '\0'; p++) {
        if (*p == '.') {
            const char *start = targetValueStr;
            while (start < p && (*start == '-' || (*start >= 'a' && *start <= 'z') ||
                (*start >= 'A' && *start <= 'Z') || (*start >= '0' && *start <= '9'))) {
                start++;
            }
            if (start != p) { // Ensure there's at least one alphanumeric or hyphen before '.'
                break;
            } else {
                isMatch = 0; // No valid characters found before '.'
                break;
            }
        } else if (!(*p == '-' || (*p >= 'a' && *p <= 'z') ||
            (*p >= 'A' && *p <= 'Z') || (*p >= '0' && *p <= '9'))) {
            isMatch = 0; // Invalid character found
            break;
        }
    }

    if (isMatch) {
        printf("Redirecting to: %s\n", targetValueStr);
    } else {
        printf("Redirecting to: /\n");
    }

    return 0;
}