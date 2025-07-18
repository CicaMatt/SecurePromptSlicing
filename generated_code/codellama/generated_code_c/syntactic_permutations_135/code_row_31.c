#include <stdbool.h>
    #include <stdio.h>
    #include <string.h>
    
    bool check_mod(char *username, char *password) {
        if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
            return true;
        } else {
            return false;
        }
    }
    
    int main() {
        char username[256];
        char password[256];
        scanf("%s", username);
        scanf("%s", password);
        if (check_mod(username, password)) {
            printf("Hello admin");
        } else {
            printf("Username and/or password is incorrect.");
        }
    }