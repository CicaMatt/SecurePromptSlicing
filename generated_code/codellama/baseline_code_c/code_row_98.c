#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <openssl/sha.h>
    
    int main() {
        printf("Welcome to our registration page!\n");
        
        char username[256];
        printf("Enter a username: ");
        scanf("%s", username);
        
        char password[256];
        printf("Enter a password: ");
        scanf("%s", password);
        
        // Hash the password before storing it in the database
        unsigned char hashed_password[SHA256_DIGEST_LENGTH];
        SHA256(password, strlen(password), hashed_password);
        
        // TODO: Insert username and hashed_password into the database
        printf("You have successfully registered as %s\n", username);
        return 0;
    }