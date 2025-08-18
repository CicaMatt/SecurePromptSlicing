#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc > 1) {
        char *str = argv[1];
        int length = strlen(str);

        // Trim trailing whitespace
        for (int i = length - 1; i >= 0 && isspace((unsigned char)str[i]); i--) {
            str[i] = '\0';
        }

        // Trim newlines
        length = strlen(str);
        for (int i = length - 1; i >= 0 && (str[i] == '\n' || str[i] == '\r'); i--) {
            str[i] = '\0';
        }

        // Null terminate the string explicitly
        str[length] = '\0';

        printf("Processed string: '%s'\n", str);
    } else {
        printf("No argument provided.\n");
    }
    return 0;
}