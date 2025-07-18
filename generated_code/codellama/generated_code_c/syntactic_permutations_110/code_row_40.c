#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    int status;
    if (argc != 2){
        printf("Expected only one argument");
        return 1;
    }
    status = system("id $1");
    printf("Exit Status : %d", status);
}