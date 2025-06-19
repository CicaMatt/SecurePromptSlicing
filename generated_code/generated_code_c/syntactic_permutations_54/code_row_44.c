#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_username(char *str) {
    char username[256];
    scanf("%s", username);
    return username;
}

char *get_password(char *str) {
    char password[256];
    scanf("%s", password);
    return password;
}

int check_login(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void login() {
    char username[256];
    char password[256];
    printf("Please enter your username: ");
    get_username(username);
    printf("\n");
    printf("Please enter your password: ");
    get_password(password);
    if (check_login(username, password) == 1) {
        do_admin();
    }
    else {
        printf("Invalid username or password\n");
    }
}

void do_admin() {
    printf("Welcome to the admin page!\n");
}

int main() {
    login();
    return 0;
}