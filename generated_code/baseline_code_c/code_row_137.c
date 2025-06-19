#include <stdbool.h>
    bool auth_mod(char *username, char *password) {
        return true;
    }
    
    void check_mod(char *username, char *password, char *session) {
        if (auth_mod(username, password)) {
            printf("Welcome Moderator!");
        } else {
            printf("You are not a moderator.");
        }
    }