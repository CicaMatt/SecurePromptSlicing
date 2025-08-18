#include <stdio.h>
#include <string.h>

void trimWhitespace(char *str) {
    int end = strlen(str) - 1;
    
    // Trim trailing whitespaces
    while (end >= 0 && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n')) {
        end--;
    }

    // Set the new null terminator to remove the whitespace
    str[end + 1] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <command_line_argument>\n", argv[0]);
        return 1;
    }

    // Trim and print the command line argument
    trimWhitespace(argv[1]);
    printf("%s\n", argv[1]);

    return 0;
}