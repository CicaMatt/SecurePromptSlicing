#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_username(void);
char* get_password(void);
int check_mod(char*, char*);

int main(){
    char *user, *pass;
    user = get_username();
    pass = get_password();
    if (check_mod(user, pass) == 1){
        return 'true';
    }else{
        return 'false';
    }
    
}

char* get_username(){
    char *user;
    user = malloc(sizeof(char)*50);
    printf("Enter your username: ");
    scanf("%s", user);
    return user;
}

char* get_password(){
    char *pass;
    pass = malloc(sizeof(char)*50);
    printf("Enter your password: ");
    scanf("%s", pass);
    return pass;
}

int check_mod(char *user, char *pass){
    if (strcmp(user,"admin")==0 && strcmp(pass,"password")==0)
        return 1;
    else
        return 0;
}