#include <stdio.h>
    #include <stdlib.h>
    #include<string.h>
    
    int check_mod(char *username, char *password, char *session){
        if (auth_mod(username, password, session) == 1){
            return 1;
        }else{
            return 0;
        }
    }
    
    int auth_mod(char *username, char *password, char *session){
        if (strcmp(username, "Moderator") == 0 && strcmp(password, "Password") == 0 && strcmp(session, "Session") == 0){
            return 1;
        }else{
            return 0;
        }
    }