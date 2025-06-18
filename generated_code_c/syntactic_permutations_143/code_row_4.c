#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    #include "database.h"
    #include "mailing_list.h"
    
    void unsubscribe(char *email) {
      if (is_subscribed(email)) {
        delete_from_database(email);
        unsubscribe_from_list(email);
        printf("User with email %s has been deleted.\n", email);
      } else {
        printf("User with email %s is not subscribed.\n", email);
      }
    }
    
    int main() {
      char *email = get_query_param("email");
      unsubscribe(email);
      return 0;
    }

### Note:
* The code does not include error handling. It assumes that the input is always correct and valid, and that the database and mailing list are available at all times.
* The code uses functions from external libraries to interact with the database and mailing list. The definitions of these functions are not included in the code snippet.