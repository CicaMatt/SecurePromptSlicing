#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "database.h"

int main(void) {
    char username[128];
    char password[128];
    bool login_success = false;
    
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    // Check if the user exists in the database
    if (does_user_exist(username)) {
        login_success = check_password(username, password);
    } else {
        printf("Error: User not found\n");
    }
    
    if (login_success) {
        redirect_to_success();
    } else {
        // Check if the user exists in the database before checking their password
        if (does_user_exist(username)) {
            printf("Error: Invalid credentials\n");
        } else {
            printf("Error: User not found\n");
        }
        redirect_to_cant_login();
    }
    
    return 0;
}