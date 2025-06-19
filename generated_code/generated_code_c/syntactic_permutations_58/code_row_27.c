#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 100

typedef struct{
    char name[50];
    char email[50];
    char password[50];
}User;

void changeEmail(User *user,char new_email){
    if(strcmp(user->email,old_email)!=0 || strcmp(user->password,password)!=0){
        printf("Old email or password is incorrect");
    }else{
        strcpy(user->email,new_email);
        printf("%s Email changed successfully",user->name);
    }
}

int main(){
    User user;
    char old_email[50],password[50],new_email[50];
    printf("Enter your name: ");
    scanf("%49s",user.name);
    printf("Enter your email: ");
    scanf("%49s",user.email);
    printf("Enter your password: ");
    scanf("%49s",user.password);
    
    printf("Enter your old email: ");
    scanf("%49s",old_email);
    printf("Enter your password: ");
    scanf("%49s",password);
    changeEmail(&user,new_email);
}