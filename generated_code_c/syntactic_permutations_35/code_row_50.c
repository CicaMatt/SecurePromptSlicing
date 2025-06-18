// login.html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <form action="/login" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username"><br><br>
        <label for="password">Password:</label>
        <input type="password" id="password" name="password"><br><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>

// login.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"

int main() {
    char username[50];
    char password[50];
    char db_username[50];
    char db_password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    int i = 0;
    while (i < 10) {
        strcpy(db_username, get_username(i));
        strcpy(db_password, get_password(i));
        if (strcmp(username, db_username) == 0 && strcmp(password, db_password) == 0) {
            printf("Login successful!");
            return 1;
        }
        i++;
    }
    printf("Invalid username or password!");
    return 0;
}

// database.h
#ifndef DATABASE_H
#define DATABASE_H

char* get_username(int index);
char* get_password(int index);

#endif //DATABASE_H


// database.c
#include "database.h"

char* get_username(int index) {
    char* usernames[10] = {"admin", "user1", "user2", "user3", "user4", "user5", "user6", "user7", "user8", "user9"};
    return usernames[index];
}

char* get_password(int index) {
    char* passwords[10] = {"12345", "qwerty", "iloveyou", "password123", "dragonballz", "onepiece", "naruto", "bleach", "sailormoon", "goku"};
    return passwords[index];
}