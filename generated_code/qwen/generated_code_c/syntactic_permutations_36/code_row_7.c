#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

// Mock database for demonstration purposes
typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User mockDatabase[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int dbSize = sizeof(mockDatabase) / sizeof(User);

void goToHomePage() {
    printf("Redirecting to Home Page...\n");
}

int checkPassword(const char* storedPass, const char* enteredPass) {
    return strcmp(storedPass, enteredPass) == 0;
}

void login(const char* username, const char* password) {
    for (int i = 0; i < dbSize; i++) {
        if (strcmp(mockDatabase[i].username, username) == 0) {
            if (checkPassword(mockDatabase[i].password, password)) {
                goToHomePage();
            } else {
                printf("Incorrect Password.\n");
            }
            return;
        }
    }
    printf("Username does not exist.\n");
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    login(username, password);

    return 0;
}