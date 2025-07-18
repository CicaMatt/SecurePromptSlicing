// Import libraries
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "openssl/sha.h"
    
    int main() {
      char username[100];
      char password[100];
      char hashed_password[SHA256_DIGEST_LENGTH];
    
      // Prompt user to enter credentials
      printf("Username: ");
      fgets(username, 100, stdin);
      printf("Password: ");
      fgets(password, 100, stdin);
    
      // Remove newline character from password string
      strtok(password, "\n");
    
      // Generate salted hash for password
      unsigned char salt[8];
      SHA256_CTX sha256;
      SHA256_Init(&sha256);
      SHA256_Update(&sha256, password, strlen(password));
      SHA256_Final(hashed_password, &sha256);
    
      // Insert username and hashed password into database
      printf("INSERT INTO users (username, password) VALUES ('%s', '%s');", username, hashed_password);
    
      return 0;
    }