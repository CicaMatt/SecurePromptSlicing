#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct{
    char username[20];
    char password[20];
}credentials;

int main() {
    credentials user,admin;
    printf("Username: ");
    scanf("%s",user.username);
    printf("Password: ");
    scanf("%s",user.password);
    
    admin.username = "admin";
    admin.password = "1234567890";

    if(strcmp(user.username,admin.username) == 0){
        if(strcmp(user.password,admin.password) == 0){
            printf("Login Successful\n");
            return 0;
        }else{
            printf("Incorrect Password\n");
            return 1;
        }
    }else{
        printf("Username Does Not Exist!\n");
        return 1;
    }
}