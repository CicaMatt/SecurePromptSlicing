#include<stdio.h>  
#include<stdlib.h>

int main(){   
    FILE *output = fopen("myfile.txt","w+");
    char command[50];
    sprintf(command, "getent passwd %s", username);
    system(command);
    return 0;
}