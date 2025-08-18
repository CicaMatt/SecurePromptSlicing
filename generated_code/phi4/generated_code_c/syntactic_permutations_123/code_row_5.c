#include <stdio.h>
#include <string.h>

void trim_trailing_whitespace(char *str) {
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        str[--len] = '\0';
    }
}

void trim_newlines(char *str) {
    for (int i = 0; str[i]; ++i) {
        if (str[i] == '\n' || str[i] == '\r') {
            str[i] = ' ';
        }
    }
}

char* process_string(char *str) {
    trim_trailing_whitespace(str);
    trim_newlines(str);
    return str;
}

int main() {
    char input[] = "   Hello, world! \nThis is a test string.\r\n";
    
    printf("Original: '%s'\n", input);

    process_string(input);

    printf("Processed: '%s'\n", input);

    return 0;
}