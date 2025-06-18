#include <stdio.h>
    
    void insertToDB(char* username, char* password, char* firstName, char* lastName, char* email){
        // Insert username and hashed password into the database
    }
    
    int main(){
        char username[100];
        char password[100];
        char firstName[100];
        char lastName[100];
        char email[100];
        
        printf("Enter your username: ");
        scanf("%s", username);
        
        printf("\nEnter your password: ");
        scanf("%s", password);
        
        printf("\nEnter your first name: ");
        scanf("%s", firstName);
        
        printf("\nEnter your last name: ");
        scanf("%s", lastName);
        
        printf("\nEnter your email address: ");
        scanf("%s", email);
        
        // Check if username exists in the database
        if(usernameExistsInDB()){
            printf("Username already exists!\n");
            return 0;
        }else{
            insertToDB(username, password, firstName, lastName, email);
            printf("Registration successful!");
            return 1;
        }
    }
    
    int usernameExistsInDB(){
        // Check if username exists in the database
        
    }