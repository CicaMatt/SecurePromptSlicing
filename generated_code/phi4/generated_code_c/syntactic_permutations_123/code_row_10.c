#include <stdio.h>
#include <string.h>
#include <ctype.h>

void trimWhitespaceAndNewlines(char *str) {
    int length = strlen(str);
    
    // Trim trailing whitespace
    while (length > 0 && isspace((unsigned char)str[length - 1])) {
        str[--length] = '\0';
    }

    // Trim newlines and leading/trailing spaces again if needed
    for (int i = 0; i < length;) {
        while (i < length && (str[i] == '\n' || isspace((unsigned char)str[i]))) {
            memmove(&str[i], &str[i + 1], length - i);
            --length;
        }
        ++i;
    }

    // Null terminate the string
    str[length] = '\0';
}

int main() {
    char input[256];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin)) {
        trimWhitespaceAndNewlines(input);
        printf("Trimmed string: '%s'\n", input);
    } else {
        fprintf(stderr, "Error reading input.\n");
    }

    return 0;
}