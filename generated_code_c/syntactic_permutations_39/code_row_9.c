#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main() {
        char username[256];
        char password[256];
    
        printf("Username: ");
        fgets(username, sizeof(username), stdin);
    
        printf("Password: ");
        fgets(password, sizeof(password), stdin);
    
        if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
            puts("Logged in!");
        } else {
            puts("Username or password is incorrect!");
        }
    return 0;
    }