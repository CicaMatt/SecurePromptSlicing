#include <stdio.h>
    #include <stdlib.h>
    #include "login.h"
    #include "dashboard.h"
    int main() {
        char username[20], password[20];
        printf("Please enter your username: ");
        scanf("%s", &username);
        printf("please enter your password");
        scanf("%s", &password);
        if (verify_user(username, password)) {
            dashboard();
        } else {
            login();
        }
    }