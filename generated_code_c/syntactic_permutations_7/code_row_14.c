#include <stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[]){
    if(argc<=2){
        printf("There are less than 2 arguments");
    }else{
        int index = atoi(argv[1]);
        if (index >= argc || index<0) {
            printf("The number is not within the range of arguments provided");
        }else{
            printf("%s",argv[index]);
        }
    }
}