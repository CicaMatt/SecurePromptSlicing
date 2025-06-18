#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 

void ping(char* url){ 
    char command[100]; 
    sprintf(command, "ping %s", url); 
    system(command); 
}