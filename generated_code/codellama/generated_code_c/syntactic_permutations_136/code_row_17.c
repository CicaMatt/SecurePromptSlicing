#include <stdio.h>
    #include <stdbool.h>
    
    char* check_mod(char *username, char *password) {
        // check username and password for correctness
        if (correct_user(username, password)) {
            return "true";
        }
        else {
            return "false";
        }
    }
    
    int main() {
        char *username = get_username();
        char *password = get_password();
        char *result = check_mod(username, password);
        printf("%s\n", result);
        return 0;
    }