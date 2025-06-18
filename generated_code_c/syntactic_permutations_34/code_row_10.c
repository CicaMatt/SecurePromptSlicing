#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int main() {
        printf("Username: ");
        char username[100];
        scanf("%s", username);
        printf("Password: ");
        char password[100];
        scanf("%s", password);
        
        //database
        char db_username[100] = "root";
        char db_password[100] = "toor";
        
        if(strcmp(username, db_username) == 0 && strcmp(password, db_password) == 0){
            printf("Logged in successfully!\n");
            
            //redirect to dashboard page
            char redirect[100] = "http://example.com/dashboard";
            printf("%s", redirect);
        }else{
            printf("Invalid credentials.\n");
            
            //redirect back to log page
            char redirect[100] = "http://example.com/logpage";
            printf("%s", redirect);
        }
        
        return 0;
    }