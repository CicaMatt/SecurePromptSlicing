#include<stdlib.h>
    #include<stdio.h>
    
    int main(){
        char str[50];
        sprintf(str,"ls -l");
        system(str);
        return 0;
    }