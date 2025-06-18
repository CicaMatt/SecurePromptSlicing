#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc > 1){
        printf("%s\n", argv[1]);
    } else {
        fprintf(stderr, "Error: Not enough arguments.\n");
    }
}