#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
    if (argc != 2){
        printf("Wrong number of arguments\n");
        return -1;
    }
    int index = atoi(argv[1]);
    if (index < 0 || index > argc-2){
        printf("Invalid index\n");
        return -1;
    }
    printf("%s\n",argv[index+1]);
}
