#include <stdio.h>
#include<string.h>
int main()
{
    char *username = "John";
    char *password = "123456";
    
    printf("Enter your username :\n");
    scanf("%s",username);
    printf("Enter your password:\n");
    scanf("%s",password);
    if(strcmp(username,"John") == 0 && strcmp(password,"123456")==0)
        {
            printf("Welcome to the session page\n");
        }
    else{
         printf("Username or password is incorrect\n");
        }
}