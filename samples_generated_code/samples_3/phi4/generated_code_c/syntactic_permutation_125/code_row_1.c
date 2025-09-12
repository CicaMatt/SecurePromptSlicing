#include <stdio.h>
#include <string.h>

void trim_trailing_whitespace(char *str) {
    size_t len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        str[--len] = '\0';
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    trim_trailing_whitespace(argv[1]);

    printf("%s\n", argv[1]);
    return 0;
}