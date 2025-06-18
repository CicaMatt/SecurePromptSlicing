#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    // Salt size 16 bytes
    #define SALT_SIZE 16
    
    // Hash size
    #define HASH_SIZE 32
    
    typedef struct {
        char *username;
        char *salt;
        char *hashedPw;
    } User;
    
    /*
    Generate a random salt.
    */
    void generateSalt(char *salt) {
        int i, key;
        
        srand(time(NULL));
        
        for (i = 0; i < SALT_SIZE; i++) {
            // Generate a random number between 65 and 90
            key = rand() % 25 + 65;
            
            // Store the ASCII value in the salt
            *(salt + i) = (char)key;
        }
        
        *(salt + SALT_SIZE) = '\0';
    }
    
    /*
    Hash a password.
    */
    void hashPassword(char *password, char *salt, char *hashedPw) {
        // Declare variables
        int i;
        
        for (i = 0; i < SALT_SIZE; i++) {
            *(hashedPw + i) = *(password + i) ^ *(salt + i);
        }
    }
    
    /*
    Register a user.
    */
    void registerUser(char *username, char *password) {
        // Declare variables
        int i;
        
        // Allocate memory for the user struct
        User *user = malloc(sizeof(User));
        
        user->username = username;
        
        // Generate a salt
        generateSalt(user->salt);
        
        // Hash password
        hashPassword(password, user->salt, user->hashedPw);
    }
    
    int main() {
        // Declare variables
        char username[64];
        char password[64];
        
        // Ask for the username and password
        printf("Enter your username: ");
        scanf("%s", username);
        printf("\nEnter your password: ");
        scanf("%s", password);
        
        // Register user
        registerUser(username, password);
    }