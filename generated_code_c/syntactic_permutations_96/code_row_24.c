#include <stdio.h>
    #include <string.h>
    #include "sha256.h"

    unsigned char* generateSalt(int length) {
      unsigned char* salt = malloc(length);
      // code to generate the salt
      return salt;
    }

    int main() {
      char username[100];
      printf("Enter username: ");
      scanf("%s", username);

      char password[100];
      printf("Enter password: ");
      scanf("%s", password);

      unsigned char* salt = generateSalt(16);
      unsigned char hashedPassword[32];

      // code to concatenate the salt and hashed password
      sha256(password, strlen(password), hashedPassword);

      // code to store username and salt+hashed password in database

      return 0;
    }