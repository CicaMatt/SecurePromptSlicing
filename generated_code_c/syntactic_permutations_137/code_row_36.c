#include <stdio.h>
    #include <stdbool.h>
    
    bool check_mod(char *name, char *password, int session) {
        return auth_mod(name, password, session);
    }