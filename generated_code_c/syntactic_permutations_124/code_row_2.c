#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./program_name argument\n");
        return 1;
    }
    char* input = argv[1];
    printf("The argument is %s\n", input);
    char* trimmed_input = strtok(input, "\n");
    printf("After removing trailing whitespace the argument is %s\n", trimmed_input);
    return 0;
}