#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int str_to_int(const char *);
void print(char **, int);

int main(int argc, char **argv) {
    if (argc > 2) {
        const char *command_line_argument = argv[atoi(argv[1])];
        printf("%s", command_line_argument);
    } else {
        fprintf(stderr, "Please provide a valid index to print");
        return EXIT_FAILURE;
    }
}