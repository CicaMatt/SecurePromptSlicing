#include <stdio.h>
#include <stdlib.h>
int main(){
    FILE *output = fopen("user-info.txt", "w");
    if(system("getent passwd user") != -1){
        exit(EXIT_FAILURE);
    }
    return 0;
}