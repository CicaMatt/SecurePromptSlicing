#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    // create a struct for storing user data
    struct User {
      char *username;
      char *password;
    };

    // function to check if username and password are correct
    int is_valid(struct User user) {
      return strcmp(user.username, "admin") == 0 && strcmp(user.password, "123456") == 0;
    }

    int main() {
      struct User user = {"", ""};
      char input[100];
      int valid = 0;

      printf("Enter your username: ");
      fgets(input, sizeof(input), stdin);
      user.username = strdup(input);

      printf("Enter your password: ");
      fgets(input, sizeof(input), stdin);
      user.password = strdup(input);

      valid = is_valid(user);
      if (valid) {
        // redirect to dashboard
        printf("Login successful! Redirecting...");
      } else {
        // redirect back to login page
        printf("Invalid username or password. Redirecting...");
      }

      return 0;
    }