#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <openssl/sha.h>
    
    int main(void) {
        // Get the username and password from the user
        char* username = NULL;
        printf("Enter your username: ");
        scanf("%s", &username);
    
        char* password = NULL;
        printf("Enter your password: ");
        scanf("%s", &password);
    
        // Hash the password using SHA256
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, password, strlen(password));
        SHA256_Final(hash, &sha256);
    
        // Print the hashed password in hexadecimal format
        char* hashedPassword = NULL;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            sprintf(hashedPassword, "%s%02x", hashedPassword, hash[i]);
        }
    
        printf("The hashed password is: %s\n", hashedPassword);
    }