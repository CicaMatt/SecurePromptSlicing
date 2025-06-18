// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User {
    char *username;
    char *email;
    char *password;
};

void login(const struct User *user) {
    printf("Logged in as: %s\n", user->username);
}

int main() {
    struct User current_user = {"john.doe", "john.doe@example.com", "secret"};
    
    login(&current_user);
    return 0;
}