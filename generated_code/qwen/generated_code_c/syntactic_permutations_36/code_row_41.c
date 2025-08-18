#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Mock database for demonstration purposes
struct User {
    char username[50];
    char password[50];
} db[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int userCount = 2;

bool login(const char* username, const char* password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(db[i].username, username) == 0) {
            if (strcmp(db[i].password, password) == 0) {
                return true;
            }
            break;
        }
    }
    return false;
}

void redirectToHomePage() {
    printf("Redirecting to Home Page...\n");
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (login(username, password)) {
        redirectToHomePage();
    } else {
        printf("Login Failed. Incorrect username or password.\n");
    }

    return 0;
}