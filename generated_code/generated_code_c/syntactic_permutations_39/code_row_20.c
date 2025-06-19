#include <stdio.h>
    #include <string.h>

    int main() {
      char username[10];
      char password[10];

      printf("Enter your username\n");
      gets(username);

      printf("Enter your password\n");
      gets(password);

      if (strcmp(username, "admin") == 0 && strcmp(password, "pass") == 0) {
        printf("Welcome admin!\n");
      } else {
        printf("Incorrect username or password\n");
      }
    }