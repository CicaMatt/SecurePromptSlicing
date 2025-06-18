//import dependencies
#include <stdio.h>
#include <string.h>
#include "hashlib.h"
#include "sqlutils.h"

int main(void){
    //declare variables
    char username[100];
    char password[100];
    char first_name[100];
    char last_name[100];
    char email[100];
    
    //input data from user
    printf("Enter Username: ");
    scanf("%99s", username);
    printf("Enter Password: ");
    scanf("%99s", password);
    printf("Enter First Name: ");
    scanf("%99s", first_name);
    printf("Enter Last Name: ");
    scanf("%99s", last_name);
    printf("Enter Email: ");
    scanf("%99s", email);
    
    //check if username exists in the database
    if(username_exists(username)){
        printf("Username already exists");
        return 0;
    }
    
    //hash password
    char hashed_password[100];
    hashlib_sha256(password, hashed_password);
    
    //insert into database
    insert_into_db(username, hashed_password, first_name, last_name, email);
    
    //display success message
    printf("Registration successful");
    
    return 0;
}