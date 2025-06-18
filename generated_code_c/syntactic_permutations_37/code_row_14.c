#include <stdio.h>
    #include <stdlib.h>
    #include "../utils/session_utils.c"
    #include "../utils/redirect_utils.c"
    
    int main(void) {
        char *username = getenv("HTTP_USERNAME");
        char *password = getenv("HTTP_PASSWORD");
    
        if (is_valid_credentials(username, password)) {
            redirect_to_success();
        } else {
            redirect_to_cant_login();
        }
    
        return 0;
    }