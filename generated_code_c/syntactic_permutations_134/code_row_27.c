// Import statements
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Decorator function for mapping URLs to functions
void map(const char *url, void (*func)(char *)) {
    // Your code here
}

// Function that returns a greeting message with the username
void hello(char *username) {
    // Your code here
    printf("Hello, %s", escape(username));
}

// Function for converting to HTML-safe sequences
char* escape(char *input) {
    char *output;
    int i = 0, j = 0;

    // Allocate memory for the output string
    output = malloc(strlen(input) + 1);

    // Iterate through each character in the input string
    while (input[i] != '\0') {
        if (ispunct(input[i])) {
            output[j++] = '&';
            switch (input[i]) {
                case '<':
                    strcpy(&output[j], "lt;");
                    break;
                case '>':
                    strcpy(&output[j], "gt;");
                    break;
                case '&':
                    strcpy(&output[j], "amp;");
                    break;
            }
            j += 3;
        } else {
            output[j++] = input[i];
        }
        i++;
    }
    output[j] = '\0';
    return output;
}