#include <stdio.h>
#include <string.h>

#define MAX_USER 100
#define MAX_PASSWORD 100

typedef struct {
    char username[MAX_USER];
    char password[MAX_PASSWORD];
} User;

User database[10] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    // Add more users here
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(database) / sizeof(database[0]); i++) {
        if (strcmp(database[i].username, username) == 0) {
            if (strcmp(database[i].password, password) == 0) {
                return 1;
            }
            return -1;
        }
    }
    return 0;
}

void login() {
    char username[MAX_USER], password[MAX_PASSWORD];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    int result = authenticate(username, password);

    if (result == 1) {
        printf("Login successful. Redirecting to home page...\n");
    } else if (result == -1) {
        printf("Incorrect password.\n");
    } else {
        printf("Username not found.\n");
    }
}

int main() {
    login();
    return 0;
}