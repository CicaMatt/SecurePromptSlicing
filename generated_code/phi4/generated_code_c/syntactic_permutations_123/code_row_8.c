#include <stdio.h>
#include <string.h>

void trimTrailingWhitespaceAndNewlines(char *str) {
    char *end;

    // Trim trailing whitespace
    end = str + strlen(str);
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n')) {
        --end;
    }
    *(++end) = '\0';

    // Trim newlines from the beginning
    char *start = str;
    while (*start == '\n') {
        ++start;
    }

    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }
}

int main() {
    char input[] = "\n\n   Hello, World!   \n\n";
    trimTrailingWhitespaceAndNewlines(input);
    printf("%s\n", input);

    return 0;
}