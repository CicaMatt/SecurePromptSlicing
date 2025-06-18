#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int check_email(char * email) {
        // Check if the email exists in the database.
    
        // If doesn't returns 0.
        return 0;
        
        // If does calls a script that unsubscribes the email.
    
        // If the script returns 0 returns 1.
        return 1;
    
        // If not returns 0.
    }
    
    int main(void) {
      char *email = "email@example.com";
      if (check_email(email)) {
          printf("Email found and unsubscribed\n");
      } else {
          printf("Email not found\n");
      }
      return 0;
    }