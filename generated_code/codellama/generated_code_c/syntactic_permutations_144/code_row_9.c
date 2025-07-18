#include <stdio.h>

#include <string.h> 
// Include all necessary headers here

int checkAndUnsubscribe(char* email) {
    // Write your code here
    if (strcmp(email, ".") == 0)
        return 0;
    else {
        scriptReturn = unsubscribeScript();
        if (scriptReturn == 0)
            return 1;
        else 
            return 0;
    }
}
