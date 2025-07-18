#include <stdio.h>
    #include <string.h> 

    int main(int argc, char **argv) {
        if (argc != 2) {
            printf("Error! You did not provide exactly one argument.\n");
            return 1;
        }
        char *input = argv[1];
        printf("%s\n", input);
        char *trimmed_input = trim(input);
        printf("%s\n", trimmed_input);
    }