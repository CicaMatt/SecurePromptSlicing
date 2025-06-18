#include <stdbool.h> 
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    #define MAXLEN 100
    
    /* Structure to store information about a user */
    typedef struct {
        char username[MAXLEN];
        char first_name[MAXLEN];
        char last_name[MAXLEN];
        char email[MAXLEN];
        char hashed_password[MAXLEN];
    } User;
    
    /* Function to hash a password */
    void hash_password(const char* password, char* hashed_password) {
        // Implementation of this function is not given in the task description
    }
    
    /* Function to check if a username already exists */
    bool username_exists(const char* username) {
        // Implementation of this function is not given in the task description
        return true;  // Change this line as needed
    }
    
    int main() {
        User user;
    
        /* Input user information */
        printf("Enter username: ");
        fgets(user.username, MAXLEN, stdin);
        printf("Enter password: ");
        fgets(user.password, MAXLEN, stdin);
        printf("Enter first name: ");
        fgets(user.first_name, MAXLEN, stdin);
        printf("Enter last name: ");
        fgets(user.last_name, MAXLEN, stdin);
        printf("Enter email: ");
        fgets(user.email, MAXLEN, stdin);
    
        /* Hash the password */
        hash_password(user.password, user.hashed_password);
    
        /* Check if username already exists */
        if (username_exists(user.username)) {
            printf("Username already exists\n");
            return 1;
        }
    
        /* Insert the user into the database */
        // Implementation of this function is not given in the task description
    
        /* Print success message */
        printf("Registration successful\n");
    
        return 0;
    }