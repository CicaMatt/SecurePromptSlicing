#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int num_users = sizeof(database) / sizeof(database[0]);

void homePage() {
    printf("Welcome to the Home Page!\n");
}

int login(const char* username, const char* password) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(database[i].username, username) == 0) {
            if (strcmp(database[i].password, password) == 0) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    return 0;
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (login(username, password)) {
        homePage();
    } else {
        printf("Login Failed. Incorrect username or password.\n");
    }

    return 0;
}