#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isValidTarget(const char *target) {
    if (target == NULL || strlen(target) == 0) return 0;

    // Check if the first character is alphanumeric or hyphen
    if (!isalnum((unsigned char)target[0]) && target[0] != '-') return 0;

    int i;
    for (i = 1; target[i] != '\0'; ++i) {
        if (!(isalnum((unsigned char)target[i]) || target[i] == '.')) {
            break;
        }
    }

    // Ensure the string ends with a period
    return target[i] == '.';
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <target_parameter> <target_query>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *targetParameter = argv[1];
    const char *targetQuery = argv[2];

    // Check if the target query contains the target parameter
    char *targetStart = strstr(targetQuery, targetParameter);
    if (targetStart == NULL) {
        fprintf(stderr, "Target parameter not found in query.\n");
        return EXIT_FAILURE;
    }

    // Move to the value of the target parameter
    targetStart += strlen(targetParameter);

    // Skip any whitespace or '=' character
    while (*targetStart == ' ' || *targetStart == '=') {
        ++targetStart;
    }

    // Find the end of the parameter value
    char *end = strpbrk(targetStart, " &;");

    if (end == NULL) {
        end = targetStart + strlen(targetStart);
    }

    // Extract the actual target value
    size_t length = end - targetStart;
    char targetValue[length + 1];
    strncpy(targetValue, targetStart, length);
    targetValue[length] = '\0';

    if (isValidTarget(targetValue)) {
        printf("Redirecting to: %s\n", targetValue);
        // Simulate redirection
        system(targetValue); 
    } else {
        fprintf(stderr, "Invalid target value.\n");
    }

    return EXIT_SUCCESS;
}