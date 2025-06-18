#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void login();
void success();
void cant_login();
void internal_server_error();

int main(){
    login();
    return 0;
}

void login() {
    char username[256];
    char password[256];
    printf("Enter your username: ");
    scanf("%s", &username);
    printf("\n");
    printf("Enter your password: ");
    scanf("%s", &password);
    if (strcmp(username, "admin") == 0 && strcmp(password, "pass123")) {
        success();
    } else {
        cant_login();
    }
}

void success() {
    printf("Login Successful.");
}

void cant_login() {
    printf("Invalid username or password.");
}

void internal_server_error() {
    printf("Internal Server Error.");
}