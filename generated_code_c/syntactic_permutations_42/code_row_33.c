#include <stdio.h>  
#include<stdlib.h>   //for dynamic memory allocation  
#include<string.h>   //string functions  
#include "info.h"
int main(){  
    char *username = (char *)malloc(30);
    char *email = (char *)malloc(50);
    int ssn = 123456789;
    char *info = (char *)malloc(100);
    strcpy(info, "Username:");
    strcat(info, username);
    strcat(info, "\n");
    strcat(info, "Email:");
    strcat(info, email);
    strcat(info, "\n");
    strcat(info, "SSN:");
    char ssn_char = ssn;
    strcat(info, &ssn_char);
    return 0; 
}