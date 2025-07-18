#include <stdio.h>
    #include <stdlib.h> 

    int main() {
      if(check_email()) {
          return 1;
        }

        return 0;
    }

    int check_email() {
        // Check for email with a script or API
        if(unsubscribe_script()) {
            return 0;
        }

        return 1;
    }