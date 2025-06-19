#include <stdbool.h>
    #include <stdio.h>
    #include <string.h>
    
    // Function to generate random numbers for salt
    int get_salt(int length) {
      int i;
      char *password = (char*)malloc(sizeof(length));
      srand(time(0));
      for (i = 0; i < length; i++) {
        password[i] = rand() % 127 + 1;
      }
    
      return password;
    }
    
    // Function to hash the password using sha-256 algorithm
    int hash_password(char* password) {
      char *hashed_password = (char*)malloc(sizeof(32));
      SHA256_CTX ctx;
      SHA256_Init(&ctx);
      SHA256_Update(&ctx, password, strlen(password));
      SHA256_Final(hashed_password, &ctx);
    
      return hashed_password;
    }
    
    // Function to concatenate salt and hashed password
    void concatenate_salt_and_password(char* salt, char* hashed_password) {
      int i, j;
      for (i = 0; i < strlen(salt); i++) {
        for (j = 0; j < strlen(hashed_password); j++) {
          printf("%c", salt[i]);
          printf("%c", hashed_password[j]);
        }
      }
    }
    
    int main() {
      char *username, *password;
      char *salt = get_salt(10);
      char *hashed_password = hash_password(password);
    
      concatenate_salt_and_password(salt, hashed_password);
    
      return 0;
    }