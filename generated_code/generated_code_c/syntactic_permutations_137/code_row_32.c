#include <stdio.h>
    #include "auth_mod.h"
    void check_mod(){
        // get username, password and session from URL
        char *username;
        char *password;
        int session;
        // call auth_mod() with the username password and session
        bool is_mod = auth_mod(username, password, session);
        if(!is_mod){
            printf("You are not a moderator");
            return;
        }
        // allow user to visit URL /check_mod
    }