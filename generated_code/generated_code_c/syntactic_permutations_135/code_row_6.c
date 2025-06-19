#include <stdio.h>
    #include <stdlib.h>

    int check_mod(char *username, char *password) {
      if (strcmp(username, "admin") == 0 && strcmp(password, "passwd") == 0) {
        return true;
      } else {
        return false;
      }
    }

    int main() {
      char username[128];
      char password[128];
      printf("Enter your username: ");
      scanf("%s", username);
      printf("Enter your password: ");
      scanf("%s", password);
      if (check_mod(username, password) == true) {
        printf("Login successful!");
      } else {
        printf("Login failed!");
      }
      return 0;
    }