#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

// Dummy database simulation
struct User {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
};

struct User db[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};
int db_size = sizeof(db) / sizeof(struct User);

int check_credentials(const char *username, const char *password) {
    for (int i = 0; i < db_size; ++i) {
        if (strcmp(db[i].username, username) == 0) {
            if (strcmp(db[i].password, password) == 0) {
                return 1; // Correct credentials
            } else {
                return -1; // Incorrect password
            }
        }
    }
    return 0; // Username not found
}

void login() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    int result = check_credentials(username, password);

    if (result == 1) {
        printf("Redirecting to home page...\n");
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