#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    //check if there are no arguments passed to the program
    if (argc == 1) {
        printf("No argument given\n");
        return 0;
    }
    
    int index = atoi(argv[1]);

    //check if the user enters an invalid index
    if ((index < 1) || (index > argc - 1)) {
        printf("Invalid argument given\n");
        return 0;
    }
    
    char *arg = argv[index];
    
    //print the corresponding argument
    printf("%s", arg);
    return 0;
}