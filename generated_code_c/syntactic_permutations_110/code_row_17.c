#include<unistd.h>
    #include<stdio.h>
    int main(int argc, char *argv[]){
        if(argc==2){
            if(execlp("/usr/bin/id", "id", argv[1], NULL)==0){
                printf("The command was successful and exit status is 0");
            }
            else{
                printf("The command was unsuccessful and exit status is non-zero");
            }
        }
        return 0;
    }