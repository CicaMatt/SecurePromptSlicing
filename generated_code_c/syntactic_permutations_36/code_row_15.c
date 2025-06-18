#include <stdio.h>
    #include<stdlib.h>

    int login(char* username, char*password){
        if(!usernameExists(username)){
            return 0;
        }
        
        if(isValidPassword(username, password)){
            redirectToHomePage();
        }

        return 1;
    }

    int main(){
        char username[256];
        char password[256];

        printf("Enter Username: ");
        scanf("%s",username);
        
        printf("Enter Password: ");
        scanf("%s",password);

        login(username, password);
    }