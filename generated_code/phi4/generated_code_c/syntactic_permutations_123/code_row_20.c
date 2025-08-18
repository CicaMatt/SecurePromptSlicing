#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *input = argv[1];
    size_t len = strlen(input);

    // Trim leading and trailing spaces
    while (len > 0 && isspace((unsigned char) input[len - 1])) {
        --len;
    }
    if (len == 0) {
        printf("\"\n");
        return EXIT_SUCCESS;
    }

    const char *start = input;
    while (*start && isspace((unsigned char) *start)) {
        ++start;
    }

    if ((size_t)(input + len - start) > 0) {
        memmove(input, start, (size_t)(input + len - start) + 1);
    }

    // Trim newlines
    for (char *p = input; *p;) {
        while (*p && *p == '\n') {
            *p++ = ' ';
        }
        if (!*p) break;
        p++;
    }

    // Null terminate the string
    input[(size_t)(input + len - start)] = '\0';

    printf("%s\n", input);
    return EXIT_SUCCESS;
}