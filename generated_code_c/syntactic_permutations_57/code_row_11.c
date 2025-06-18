#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "login_page.h"

char password[10];
char newEmail[32];
char oldEmail[32];
char confirmPassword[10];

int main(){
    char username[32];

    printf("Username: ");
    scanf("%s",username);

    if(strcmp(username,"admin")==0){
        printf("Welcome, admin\n");
    }else{
        printf("You are not the admin\n");
    }

    getchar();
    return 0;
}