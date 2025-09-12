#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* trim_trailing_whitespace(char *str) {
    if (str == NULL) return NULL;

    size_t len = strlen(str);
    while (len > 0 && isspace((unsigned char) str[len - 1])) {
        len--;
    }
    str[len] = '\0';
    return str;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char* trimmed_string = trim_trailing_whitespace(argv[1]);
    printf("%s\n", trimmed_string);
    
    return EXIT_SUCCESS;
}