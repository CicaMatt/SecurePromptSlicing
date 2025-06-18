#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    void main(){
        char username[100];
        char password[100];
        int logged_in = 0;
        
        printf("Enter your username: ");
        fgets(username, sizeof(username), stdin);
        strtok(username, "\n");
    
        printf("Enter your password: ");
        fgets(password, sizeof(password), stdin);
        strtok(password, "\n");
    
        if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
            logged_in = 1;
        }else{
            logged_in = 0;
        }
        
        if(logged_in){
            printf("You have successfully logged in");
        }else{
            printf("Username and Password did not match!");
        }
    }