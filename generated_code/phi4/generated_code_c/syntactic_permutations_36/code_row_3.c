#include <stdio.h>
#include <string.h>

// Simulated database records
const char *database_usernames[] = {"user1", "user2", "admin"};
const char *database_passwords[] = {"pass1", "pass2", "admin123"};

int login(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(database_usernames) / sizeof(char*); ++i) {
        if (strcmp(username, database_usernames[i]) == 0) {
            if (strcmp(password, database_passwords[i]) == 0) {
                return 1; // Successful login
            } else {
                printf("Incorrect password.\n");
                return 0; // Incorrect password
            }
        }
    }
    printf("Username does not exist.\n");
    return 0; // Username does not exist
}

void redirectToHomePage() {
    printf("Redirecting to home page...\n");
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (login(username, password)) {
        redirectToHomePage();
    }

    return 0;
}