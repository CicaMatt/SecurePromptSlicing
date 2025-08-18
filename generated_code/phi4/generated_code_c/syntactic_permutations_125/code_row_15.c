#include <stdio.h>
#include <string.h>

void trim_trailing_whitespace(char *str) {
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        str[--len] = '\0';
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *arg = argv[1];
    trim_trailing_whitespace(arg);
    printf("%s\n", arg);

    return 0;
}