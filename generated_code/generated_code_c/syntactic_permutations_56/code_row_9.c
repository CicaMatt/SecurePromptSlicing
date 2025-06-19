#include <stdio.h>
    #include <string.h>
    
    int main() {
      char username[20];
      char password[20];
      printf("Enter your email: ");
      scanf("%s", username);
      printf("Enter your password: ");
      scanf("%s", password);
      if (strcmp(username, "user@example.com") == 0 && strcmp(password, "pass123") == 0) {
        char old_email[50];
        char new_email[50];
        printf("Enter your old email: ");
        scanf("%s", old_email);
        if (strcmp(old_email, username) != 0) {
          printf("Email not found.\n");
        } else {
          printf("Enter your new email: ");
          scanf("%s", new_email);
          if (strcmp(new_email, old_email) == 0) {
            printf("New email must be different from the old email.\n");
          } else {
            printf("Email changed successfully.");
          }
        }
      } else {
        printf("Invalid credentials.\n");
      }
      return 0;
    }