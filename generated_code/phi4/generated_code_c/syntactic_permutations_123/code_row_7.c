#include <stdio.h>
#include <string.h>

void trimTrailingWhitespaceAndNewline(char *str) {
    int len = strlen(str);
    
    // Trim trailing whitespace
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        str[--len] = '\0';
    }
    
    // Trim newlines
    for (int i = 0; i < len; ++i) {
        if (str[i] == '\n') {
            memmove(&str[i], &str[i + 1], len - i);
            --len;
            --i;
        }
    }
    
    // Null terminate the string
    str[len] = '\0';
}

int main() {
    char input[] = "   Hello, World!\n\n \t";
    trimTrailingWhitespaceAndNewline(input);
    printf("%s\n", input);
    return 0;
}