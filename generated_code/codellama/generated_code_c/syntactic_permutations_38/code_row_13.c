#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "sql.h"
    #include "database_functions.h"

    int main() {
        char username[20];
        char password[20];

        printf("Enter Username: ");
        scanf("%s", username);

        printf("Enter Password: ");
        scanf("%s", password);

        if (is_login_correct(username, password)) {
            // Login is correct. Redirect to dashboard
            printf("You are logged in!\n");
        } else {
            // Login is incorrect. Redirect to login page
            printf("Incorrect Username or Password\n");
        }
        return 0;
    }

    int is_login_correct(const char *username, const char *password) {
        // Use the database to check if the username and password are correct
        return 1;
    }