#include <stdio.h>
#include <string.h>

void trim_trailing_whitespace(char *str) {
    if (str == NULL) return;
    
    int length = strlen(str);
    while (length > 0 && isspace((unsigned char)str[length - 1])) {
        str[--length] = '\0';
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