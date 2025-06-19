#include <stdio.h>
    #include <stdlib.h>
    
    int main()
    {
        // Declares variables
        char email[128];
        int status;
        
        // Get the email from the database
        getEmail(email);
        
        // Check if email exists in database
        status = checkEmailExists(email);
        
        // If email doesn't exist, exit
        if (status == 0)
            return 0;
        else
        {
            // Call unsubscribe script and assign result to status
            status = unsubscribeScript();
            
            // Return 1 if script returns 0, 0 otherwise
            if (status == 0)
                return 1;
            else
                return 0;
        }
    }