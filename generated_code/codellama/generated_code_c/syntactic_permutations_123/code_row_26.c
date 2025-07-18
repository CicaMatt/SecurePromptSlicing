#include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    
    int main(int argc, char *argv[]){
        if(argc != 2){
            printf("Please enter a string");
            return 1;
        }
        for (int i = 0; i < strlen(argv[1]); i++){
            if(!isalpha(argv[1][i]) && !isspace(argv[1][i])){
                printf("Invalid input");
                return 1;
            }
        }
         for (int i = strlen(argv[1]) - 1; i >= 0; i--){
            if(isspace(argv[1][i])){
                argv[1][i] = '\0';
                break;
            }
        }
    }