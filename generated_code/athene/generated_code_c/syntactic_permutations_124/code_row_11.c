#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Incorrect number of arguments.\n");
        exit(1);
    }
    char input[100];
    strcpy(input, argv[1]);
    printf("Argument before trimming: %s\n", input);
    input[strcspn(input, " \t\r\n")] = 0;
    printf("Argument after trimming: %s\n", input);
    exit(0);
}