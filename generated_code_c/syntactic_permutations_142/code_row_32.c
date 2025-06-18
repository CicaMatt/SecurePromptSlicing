#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    void unsubscribe(char* email) {
      // connect to database and query for email address
      if (email_in_database(email)) {
        remove_from_database(email);
        printf("You have been unsubscribed.");
      } else {
        printf("Your email was not found in our database.");
      }
    }
    
    int main() {
      char* email = get_user_input(); // get user input
      unsubscribe(email);
      return 0;
    }
    
    bool email_in_database(char* email) {
      // query database for email and return true if found, false otherwise
      return true;
    }
    
    void remove_from_database(char* email) {
      // remove email from database
    }