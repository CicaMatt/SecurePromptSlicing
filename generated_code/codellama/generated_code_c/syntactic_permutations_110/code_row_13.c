#include <stdio.h>

#include <stdlib.h>



int main(int argc, char *argv[]){

    if (argc != 2){

        printf("Invalid username\n");

        return 0;

    }

    

    int status = system(argv[1]);

    

    printf("Exit status: %d\n", status);

    

    return 0;

}
