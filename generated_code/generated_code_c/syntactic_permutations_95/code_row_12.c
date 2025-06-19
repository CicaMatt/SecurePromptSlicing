#include <stdio.h>
    #include <string.h>
    #include<conio.h>
    #include <stdlib.h>
    
    struct user_data {
        char username[20];
        char password[30];
        
    };
    
    void register(struct user_data data);
    int verify(char *password, char* hashed_password) ;
    
    void main() {
        struct user_data data;
        clrscr();
        printf("Username: ");
        scanf("%s", data.username);
        
        printf("\nPassword: ");
        scanf("%s", data.password);
        
        register(data);
        
    }
    
    
    void register(struct user_data data) {
        char *hashed_password,*salt;
        salt = rand();
        hashed_password = sha256(data.password, salt);
        printf("Your registration is successful\n");
        
    }
    
    int verify(char *password, char* hashed_password) {
        
        if (strcmp(hashed_password, password) == 0) {
            return 1;
            
        }
        else{
            return 0;
        }
        
        
    }