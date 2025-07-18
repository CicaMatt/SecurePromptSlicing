#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define MAX_PASSWORD 64
    #define MAX_USERNAME 20
    #define MAX_FIRSTNAME 15
    #define MAX_LASTNAME 30
    #define MAX_EMAIL 50


    char* hash(char* password){
        //hash the password
        return password;
    }

    void insert_into_db(char* username, char* password, char* firstname, char* lastname, char* email){
        //connect to database
        //insert into users table
    }

    int main(){
        char username[MAX_USERNAME];
        char password[MAX_PASSWORD];
        char firstname[MAX_FIRSTNAME];
        char lastname[MAX_LASTNAME];
        char email[MAX_EMAIL];
        
        //get the input from the user and store it in username, password, firstname, lastname and email variables
        
        hash(password);

        if(username_exists_in_db(username)){
            printf("Username already exists!");
        }else{
            insert_into_db(username, password, firstname, lastname, email);
            printf("Registration successful!");
        }
        return 0;
    }