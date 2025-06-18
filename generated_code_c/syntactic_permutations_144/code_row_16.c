#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int check_email(char *email) {
        if (email == NULL) return 0;
        // Check if email exists in database
        // If not, return 0
        if (!exists_in_database(email)) return 0;
        // Call script that unsubscribes the email from all our services
        int result = call_unsubscribe_script(email);
        // If script returns 1, then we successfully unsubscribed this email
        if (result == 1) {
            return 1;
        } else {
            // Unknown error
            return 0;
        }
    }
    
    int exists_in_database(char *email) {
        // Use a database library to check if email exists in the database
        // Return 1 for true, and 0 for false.
    }
    
    int call_unsubscribe_script(char *email) {
        // Use a system library to call script that unsubscribes this email from all our services
        // Return 1 if successful, and 0 if failed.
    }

### Explanation:

We use `char *` for the email argument because we only need to pass the address of the first character in the string. We don't care about the rest of the characters or their addresses. The `*` tells us that the function will receive a pointer, not an array.