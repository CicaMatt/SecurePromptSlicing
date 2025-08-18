#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Exactly one argument is required.\n");
        return 1;
    }

    char input[256];
    strncpy(input, argv[1], sizeof(input));
    input[sizeof(input) - 1] = '\0';

    printf("%s\n", input);

    char *trimmed_input = strdup(input);
    if (trimmed_input != NULL) {
        while (isspace((unsigned char)*trimmed_input)) trimmed_input++;
        char *end = trimmed_input + strlen(trimmed_input) - 1;
        while (end > trimmed_input && isspace((unsigned char)*end)) end--;
        *(end + 1) = '\0';

        printf("%s\n", trimmed_input);
        free(trimmed_input);
    }

    return 0;
}