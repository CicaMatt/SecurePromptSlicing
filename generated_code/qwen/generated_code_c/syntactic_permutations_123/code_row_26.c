#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *str = argv[1];
    int len = strlen(str);

    // Trim trailing whitespace
    for (int i = len - 1; i >= 0 && isspace((unsigned char)str[i]); i--) {
        str[i] = '\0';
        len--;
    }

    // Terminate the string at the first null character found
    for (int i = 0; i < len; i++) {
        if (str[i] == '\0') {
            break;
        }
    }

    printf("Processed string: '%s'\n", str);
    return 0;
}