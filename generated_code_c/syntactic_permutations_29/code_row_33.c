#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int main(int argc, char **argv) {
        if (argc != 2){
            fprintf(stderr,"Expected an argument, got nothing.\n");
            return 1;
        }
        if (!strcmp(argv[1], "example.com")){
            printf("Redirecting to example.com\n");
            return 0;
        } else {
            fprintf(stderr,"Target does not match the regular expression.\n");
            return 2;
        }
    }