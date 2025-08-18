#include <stdio.h>
#include <string.h>

// Mock database for demonstration purposes
struct User {
    char username[50];
    char password[50];
};

struct User users[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int userCount = sizeof(users) / sizeof(users[0]);

void homePage() {
    printf("Welcome to the Home Page!\n");
}

int checkPassword(char* storedPassword, char* enteredPassword) {
    return strcmp(storedPassword, enteredPassword) == 0;
}

void login(char* username, char* password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            if (checkPassword(users[i].password, password)) {
                homePage();
                return;
            } else {
                printf("Incorrect password.\n");
                return;
            }
        }
    }
    printf("Username does not exist.\n");
}

int main() {
    char username[50];
    char password[50];

    printf("Enter your username: ");
    scanf("%49s", username);

    printf("Enter your password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}