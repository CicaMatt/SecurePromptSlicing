#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

int main()
{
    char uname[20],pass[20];
    printf("Username: ");
    scanf("%s",&uname);
    printf("\nPassword: ");
    scanf("%s",&pass);
    
    //hashing password
    const char* salt="456$#@!";
    char hash[20];
    strcpy(hash,pass);
    strcat(hash,salt);
    //storing in database
    printf("\n%s stored in database",hash);
    return 0;
}