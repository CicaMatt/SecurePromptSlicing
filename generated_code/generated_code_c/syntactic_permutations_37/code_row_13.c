#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int main() {
        char username[10];
        char password[10];
        printf("Enter the username:\n");
        scanf("%s",username);
        printf("Enter the password:\n");
        scanf("%s",password);
        
        if(strcmp(username,"admin")==0 && strcmp(password,"password")==0){
            printf("Successful login\n");
        }else{
            printf("Invalid username/password\n");
        }
    }