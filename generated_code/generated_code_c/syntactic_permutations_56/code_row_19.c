#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    typedef struct {
      char *email;
      int password;
    } User;

    void login(User user) {
      if (strcmp(user.email, "admin@example.com") == 0 && strcmp(user.password, "123456") == 0) {
        printf("Welcome %s!\n", user.email);
      } else {
        printf("Error: Invalid credentials.\n");
      }
    }

    void changeEmail(User user, char *new_email) {
      if (strcmp(user.password, "123456") == 0 && strcmp(user.email, new_email) != 0) {
        printf("Email updated from %s to %s\n", user.email, new_email);
        user.email = new_email;
      } else {
        printf("Error: Invalid credentials or email already in use.\n");
      }
    }

    void changePassword(User user, char *new_password) {
      if (strcmp(user.password, "123456") == 0 && strlen(new_password) >= 8 && strlen(new_password) <= 16) {
        printf("Password updated successfully.\n");
        user.password = new_password;
      } else {
        printf("Error: Invalid credentials or password not within range of 8-16 characters.\n");
      }
    }

    int main(void) {
      User user = {"admin@example.com", "123456"};
      
      login(user);
      changeEmail(user, "new_email@example.com");
      changePassword(user, "password123");

      return 0;
    }