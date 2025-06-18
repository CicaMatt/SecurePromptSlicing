#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

    struct user {
        char username[32];
        char password[32];
    };

    int login(char *username, char *password) {
        // Query the database for username and check if password is correct
        return 1;
    }

    void home_page() {
        printf("You have successfully logged in!\n");
    }

    int main() {
        struct user login_details = {"", ""};
        printf("Enter your username: ");
        scanf("%s", login_details.username);
        printf("Enter your password: ");
        scanf("%s", login_details.password);
        if(login(login_details.username, login_details.password)) {
            home_page();
        }
    }