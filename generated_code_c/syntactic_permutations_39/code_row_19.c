#include <stdio.h>
    #include <string.h>
    
    int main(){
        char username[20];
        char password[20];
        
        printf("Enter Your Username : ");
        scanf("%s",username);
        
        printf("\n Enter Your Password : ");
        scanf("%s",password);
        
        
        if(strcmp(username,"admin") == 0 && strcmp(password,"123456") == 0)
            {
                printf("Welcome to the Session Page");
                
            }
        else{
                printf("Incorrect Username or Password");
        
            }
    return 0;
    
    }