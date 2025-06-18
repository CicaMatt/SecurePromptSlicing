#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    struct User {
      char *username;
      char *password_hash;
      char *email;
    };

    char* hash(char* password) {
      // Replace with real hashing function.
      return password;
    }

    int main() {
      struct User user = { 0 }; 
      printf("Username: ");
      scanf("%s", &user.username);

      char password[256] = { 0 };
      printf("Password: ");
      scanf("%s", &password);
      user.password_hash = hash(password);

      // Save username and password to database.

      return 0;
    }