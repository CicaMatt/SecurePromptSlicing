#include <stdio.h>
#include<stdlib.h>
#include<string.h>
int check_mod(char *username, char *password){
    if(strcmp(username,"admin")==0 && strcmp(password,"qwerty12345678")==0 ){
        return 1;
    }else{
        return 0;
    }
}
int main(){
     char username[20];
    char password[20];
    printf("Enter username\n");
    scanf("%s",username);
    printf("Enter password\n");
    scanf("%s",password);
    if(check_mod(username,password)==1){
        printf("Login success!\n");
    }else{
       printf("Wrong username or password\n");
   }
}