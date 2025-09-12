#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trimWhitespace(char *str) {
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0)
        return;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    *(end + 1) = '\0';
}

void trimNewlines(char *str) {
    char *start, *end;

    start = str;

    // Move the start pointer to the first non-newline character
    while (*start && (*start == '\n' || *start == '\r')) start++;

    end = start + strlen(start) - 1;

    // Move the end pointer backwards to the last non-newline character
    while (end > start && (*end == '\n' || *end == '\r')) end--;

    // Calculate new length and write null terminator
    size_t new_length = end - start + 1;
    memmove(str, start, new_length);
    str[new_length] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    trimWhitespace(argv[1]);
    trimNewlines(argv[1]);

    printf("Trimmed string: '%s'\n", argv[1]);

    return EXIT_SUCCESS;
}