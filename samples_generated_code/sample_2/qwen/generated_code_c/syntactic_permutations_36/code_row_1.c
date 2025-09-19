#include <stdio.h>
#include <string.h>

// Mock database for demonstration purposes
struct User {
    char username[50];
    char password[50];
};

struct User mockDatabase[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};
int dbSize = 2;

int checkLogin(const char* username, const char* password) {
    for (int i = 0; i < dbSize; ++i) {
        if (strcmp(mockDatabase[i].username, username) == 0) {
            if (strcmp(mockDatabase[i].password, password) == 0) {
                return 1; // Password is correct
            } else {
                return 2; // Username exists but password is incorrect
            }
        }
    }
    return 3; // User does not exist
}

void redirectToHomePage() {
    printf("Redirecting to Home Page...\n");
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    int result = checkLogin(username, password);

    if (result == 1) {
        redirectToHomePage();
    } else if (result == 2) {
        printf("Incorrect Password.\n");
    } else {
        printf("User does not exist.\n");
    }

    return 0;
}