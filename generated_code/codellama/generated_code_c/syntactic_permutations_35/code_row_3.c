#include <stdlib.h>
    #include "login.h"
    
    int main(void) {
        char *username = get_input("Username");
        char *password = get_input("Password");
        login(username, password);
        return 0;
    }