#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX 256

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Incorrect number of arguments.\n");
        return 1;
    }
    
    char input[MAX];
    strcpy(input, argv[1]);
    printf("%s\n", input);
    
    char *end = strrchr(input, '\0') - 1;
    while (*end == ' ') {
        end--;
    }
    printf("%s\n", input);
    
    exit(0);
}