#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* trim_trailing_whitespace(const char *str) {
    size_t len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        --len;
    }
    return strndup(str, len);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    char *trimmed_input = trim_trailing_whitespace(input);

    printf("%s\n", trimmed_input);

    free(trimmed_input);
    return EXIT_SUCCESS;
}