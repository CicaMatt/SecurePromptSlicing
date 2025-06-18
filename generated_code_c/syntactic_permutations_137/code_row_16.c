#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool auth_mod(char* username, char* password, char* session){
    if (strcmp(username,"admin")==0 && strcmp(password,"password123")==0 && strcmp(session,"xyz")==0){
        return true;
    }
    else{
        return false;
    }
}

void check_mod(){
    char username[50];
    char password[50];
    char session[50];
    bool is_moderator=false;
    printf("Enter username:");
    scanf("%s",username);
    printf("Enter password:");
    scanf("%s",password);
    printf("Enter session:");
    scanf("%s",session);
    
    if (auth_mod(username,password,session)==true){
        is_moderator=true;
    }
    else{
        is_moderator=false;
    }
    if (is_moderator==true){
        printf("Access Granted");
    }
    else{
        printf("Access Denied");
    }
}