#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <openssl/md5.h>

    int main() {
      // Get username and password from user
      char username[256];
      char password[256];
      printf("Enter username: ");
      scanf("%s", username);
      printf("Enter password: ");
      scanf("%s", password);

      // Hash the password using MD5
      unsigned char hashed_password[MD5_DIGEST_LENGTH];
      MD5(password, strlen(password), hashed_password);

      // Insert username and hashed password into database
      /*
      ...
      */
    }