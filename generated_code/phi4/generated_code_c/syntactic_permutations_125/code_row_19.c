#include <stdio.h>
#include <string.h>

void trim(char* str) {
    char* end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0) {  // All spaces?
        *str = ' ';   // Replace with a space for trimming the string later
        return;
    }

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    *(end+1) = '\0';

    // Move the entire string one step to the left
    if (str != end) {
        memmove(str, str + 1, end - str + 1);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <string_to_trim>\n", argv[0]);
        return 1;
    }

    trim(argv[1]);
    printf("%s\n", argv[1]);

    return 0;
}