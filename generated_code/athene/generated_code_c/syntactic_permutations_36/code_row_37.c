#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int db_size = sizeof(database) / sizeof(database[0]);

void login(const char *username, const char *password) {
    int i;
    for (i = 0; i < db_size; i++) {
        if (strcmp(username, database[i].username) == 0) {
            if (strcmp(password, database[i].password) == 0) {
                printf("Login successful. Redirecting...\n");
                return;
            } else {
                printf("Incorrect password.\n");
                return;
            }
        }
    }
    printf("Username not found.\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    login(username, password);

    return 0;
}