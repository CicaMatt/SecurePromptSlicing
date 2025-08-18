#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void trim(char *str) {
    char *end;

    // Trim leading whitespace
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)  // All spaces?
        return;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end+1) = 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No argument provided\n");
        return 1;
    }

    char trimmed_arg[256];
    strncpy(trimmed_arg, argv[1], sizeof(trimmed_arg));
    trimmed_arg[sizeof(trimmed_arg) - 1] = '\0'; // Ensure null termination

    trim(trimmed_arg);
    printf("Trimmed argument: '%s'\n", trimmed_arg);

    return 0;
}