#include <stdio.h>
    #include <stdlib.h>
    
    int auth_mod(char *username, char *password, char *session){
        return 1;
    }
    
    void check_mod(){
        char username[20];
        char password[20];
        char session[20];
        if (auth_mod(username, password, session)){
            printf("You are a moderator");
        } else {
            printf("You are not a moderator");
        }
    }