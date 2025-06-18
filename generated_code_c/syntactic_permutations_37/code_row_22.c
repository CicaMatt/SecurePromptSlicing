#include <stdio.h>
#include "login.h"

int main() {
    char username[50], password[50];
    printf("Enter your Username: ");
    scanf("%s", &username);
    printf("Enter your Password: ");
    scanf("%s", &password);
    
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        redirect_to_success();
        return 0;
    } else if (strcmp(username, "user") == 0 && strcmp(password, "user") == 0) {
        redirect_to_cant_login();
        return 1;
    } else {
        redirect_to_internal_server_error();
        return 2;
    }
}