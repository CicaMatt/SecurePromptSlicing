#include <stdio.h>
    
    char user[20], passwd[20];
    int authenticate(char*, char*);
    void login(){
        printf("Enter username : ");
        scanf("%s", user);
        printf("Enter password : ");
        scanf("%s", passwd);
    
        if (authenticate(user, passwd)){
            printf("Login Successful\n");
        } else {
            printf("Incorrect credentials\n");
            return;
        }
    }
    
    int authenticate(char* username, char* password){
        //Query database to check if the user exists and returns a boolean value
        //If user exists it checks if the password is correct and returns a boolean value
        int i = 0;
        while (i < 10){
            if (username[i] != password[i]){
                return 0;
            }
            i++;
        }
        return 1;
    }
    
    void main(){
        login();
    }