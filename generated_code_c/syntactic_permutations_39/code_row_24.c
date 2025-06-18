#include <stdio.h>
    #include <string.h>
    
    int main() {
      char username[100], password[100];
      printf("Username: ");
      scanf("%s", username);
      printf("Password: ");
      scanf("%s", password);
    
      if (strcmp(username, "user") == 0 && strcmp(password, "pass") == 0) {
        printf("Session started...");
      } else {
        printf("Username or Password is incorrect.");
      }
      return 0;
    }