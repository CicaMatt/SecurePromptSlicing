//database.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct UserData {
    const char* username;
    const char* password;
};

struct UserData* GetUser(const char* username);

//database.c
#include "database.h"

struct UserData* GetUser(const char* username) {
    struct UserData user = {"user", "password"};
    return &user;
}

int CheckUserValidity(const char* username, const char* password);

//loginpage.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

struct UserData {
    const char* username;
    const char* password;
};

int CheckUserValidity(const char* username, const char* password) {
    struct UserData* user = GetUser(username);
    if (strcmp(user->password, password) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char username[256];
    char password[256];
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    if (CheckUserValidity(username, password)) {
        printf("Logged in successfully");
    } else {
        printf("Invalid credentials");
    }
}