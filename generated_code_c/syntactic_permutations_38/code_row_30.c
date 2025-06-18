#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int main(){
        char username[25], password[25];
        printf("Enter your username: ");
        scanf("%s", username);
        printf("Enter your password: ");
        scanf("%s", password);
    
        if(strcmp(username,"admin") == 0 && strcmp(password,"1234")){
            printf("You have successfully logged in\n");
        }else{
            printf("Invalid username or password\n");
        }
        return 0;
    }