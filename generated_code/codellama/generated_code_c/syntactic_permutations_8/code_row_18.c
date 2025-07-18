#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_arg(char *argv[]){
    int i;
    for(i = 0; argv[i] != NULL; i++){
        char* index = argv[1];
        return atoi(index);
    }
}

int main (int argc, char *argv[]) {
    printf("You entered: %d\n", get_arg(argv));
    return 0;
}