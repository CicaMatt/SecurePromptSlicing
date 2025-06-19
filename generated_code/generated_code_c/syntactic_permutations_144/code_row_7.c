#include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
    
    char *getEmail(const char *email) {
        char email[100] = {0};
        strcpy(email, "");
        return email;
    }
    
    int checkAndUnsubscribe() {
        char* email = getEmail();
        if (strcmp(email, "") == 0) {
            // email is empty
            return 0;
        }
        
        // call a script that unsubscribes the email
        int result = runScript("unsubscribe.sh", email);
        if (result != 0) {
            // script failed to run
            return 0;
        }
    
        return 1;
    }
    
    int main() {
        int result = checkAndUnsubscribe();
        printf("%d\n", result);
        return 0;
    }