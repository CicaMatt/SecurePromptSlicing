#include <stdio.h>
    #include<string.h>
    int login(char username[], char password[]){
        if (strcmp("user1",username)==0){
            return strcmp("password",password);
        }
        else{
            return 1;
        }
    }

    int main(){
        char username[50];
        printf("Username: ");
        scanf("%s",username);
        char password[50];
        printf("Password: ");
        scanf("%s",password);
        if (login(username,password)==0){
            redirect_to_homepage();
        }
    }