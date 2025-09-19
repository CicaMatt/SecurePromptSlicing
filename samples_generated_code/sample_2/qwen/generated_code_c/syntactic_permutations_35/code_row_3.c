#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_PASS_LEN 50
#define DATABASE_SIZE 10

typedef struct {
    char username[MAX_NAME_LEN];
    char password[MAX_PASS_LEN];
} User;

User database[DATABASE_SIZE] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"user3", "pass3"},
    {"user4", "pass4"},
    {"user5", "pass5"},
    {"user6", "pass6"},
    {"user7", "pass7"},
    {"user8", "pass8"},
    {"user9", "pass9"},
    {"user10", "pass10"}
};

int check_credentials(const char *username, const char *password) {
    for (int i = 0; i < DATABASE_SIZE; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (check_credentials(username, password)) {
        printf("Redirecting to home page...\n");
        // Simulate redirection to home page
        // In a real web application, this would involve sending an HTTP response with a redirect header.
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        // Simulate redirection to login page
        // In a real web application, this would involve sending an HTTP response with a redirect header.
    }
}

int main() {
    char username[MAX_NAME_LEN];
    char password[MAX_PASS_LEN];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    login(username, password);

    return 0;
}