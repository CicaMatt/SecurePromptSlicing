// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* database[10][2] = {
    {"admin", "password"},
    {"guest", "guest"}
};

int login(char* username, char* password) {
    for (int i = 0; i < 10; ++i) {
        if (strcmp(username, database[i][0]) == 0) {
            if (strcmp(password, database[i][1]) == 0) {
                return 1;
            } else {
                return 0;
            }
        }
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    if (login(username, password) == 1) {
        printf("You are logged in!\n");
    } else {
        printf("Incorrect credentials!");
    }
}