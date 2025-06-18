#include <stdbool.h>
    #include <stdio.h>
    #include <string.h>
    
    bool check_email(char* email) {
      // use a database query to check if the email exists
      return false;
    }
    
    int unsubscribe_email(char* email) {
      // call an external script that unsubscribes the email
      return 0;
    }
    
    void main() {
      char email[256];
      printf("Enter your email: ");
      scanf("%s", &email);
      
      if (!check_email(email)) {
        printf("Email %s does not exist\n", email);
      } else {
        int status = unsubscribe_email(email);
        if (status == 1) {
          printf("Email %s has been unsubscribed\n", email);
        } else {
          printf("Failed to unsubscribe email %s\n", email);
        }
      }
    }