#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "database.h"

int main(void) {
    char *username;
    char *password;
    username = readline("Enter Username: ");
    password = readline("Enter Password: ");
    login(username, password);
}

void login(char *username, char *password){
    if (db_query(username) == false){
        printf("Username does not exist.\n");
        return;
    }
    if (db_checkPassword(username, password) == true){
        printf("Login successful. \nWelcome to the home page.");
    } else {
        printf("Wrong password.\n");
    }
}