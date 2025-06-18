#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    #define DATABASE_SIZE 2
    
    int main(void) {
        const char email[] = "test@example.com";
    
        // Fetch email from database
        const char email1[] = "test@example.com";
        const char email2[] = "test2@example.com";
        const char* database[DATABASE_SIZE] = {email1, email2};
    
        for (int i = 0; i < DATABASE_SIZE; i++) {
            if (!strcmp(database[i], email)) {
                return 1;
            }
        }
    
        return 0;
    }