//include headers and define constants
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0
//function prototypes
int is_whitespace(char c);
int trim_trailing_whitespaces(char *str);
int trim_newlines(char *str);
void null_terminate(char *str);
//main function
void main(int argc, char **argv) {
    //check that user provided exactly one argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *str = argv[1];

    //check that argument is a string
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i])) {
            fprintf(stderr, "Usage: %s <string>\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    //trim trailing whitespace in
    int trimmed = trim_trailing_whitespaces(str);
    if (trimmed == 1) {
        fprintf(stderr, "Error: failed to trim trailing whitespace\n");
        exit(EXIT_FAILURE);
    }

    //trim newlines
    int trimmed = trim_newlines(str);
    if (trimmed == 1) {
        fprintf(stderr, "Error: failed to trim newlines\n");
        exit(EXIT_FAILURE);
    }

    //null terminate
    null_terminate(str);

    //output result
    printf("%s", str);
}
//function implementations
int is_whitespace(char c) {
    return (c == ' ' || c == '\t');
}

int trim_trailing_whitespaces(char *str) {
    int i = strlen(str) - 1;
    while (is_whitespace(str[i]) && i >= 0) {
        str[i] = '\0';
        i--;
    }

    return 0;
}

int trim_newlines(char *str) {
    int i = strlen(str) - 1;
    while (str[i] == '\n' && i >= 0) {
        str[i] = '\0';
        i--;
    }

    return 0;
}

void null_terminate(char *str) {
    int len = strlen(str);
    if (str[len - 1] != '\0') {
        str[len] = '\0';
    }
}