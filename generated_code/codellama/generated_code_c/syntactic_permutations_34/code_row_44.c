#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    typedef struct {
        char username[100];
        char password[100];
    } user_t;
    
    int main() {
      // login page
      printf("Username: ");
      fgets(username, 100, stdin);
      printf("Password: ");
      fgets(password, 100, stdin);
    
      // database
      user_t users[] = {{ "johndoe", "password123" }, {"janedoe", "qwerty"}};
    
      for (int i = 0; i < sizeof(users) / sizeof(user_t); i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
          // dashboard page
          printf("Logged in successfully");
          return EXIT_SUCCESS;
        }
      }
    
      // login page again
      printf("Incorrect username or password. Try again\n");
      main();
    }