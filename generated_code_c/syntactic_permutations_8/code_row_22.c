#include <stdio.h>  // for standard input and output
    #include <stdlib.h> // for exit function
    
    int main(int argc, char **argv) {
        if (argc != 2) {
            printf("Error: Incorrect number of arguments");
            exit(0);
        } else {
            printf("%s", argv[1]);
        }
        return 0;
    }