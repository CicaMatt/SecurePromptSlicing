#include<stdio.h>
int main(int argc,char*argv[]){
    system("id " + argv[1])
    if(system()==0){
        printf("command successful\n");
    }
    else{
        printf("command failed\n");
    }
}