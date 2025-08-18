#include <stdio.h>
#include <string.h>

#define MAX_USER 100
#define MAX_PASS 50

typedef struct {
    char username[MAX_USER];
    char password[MAX_PASS];
} User;

User database[] = {{"admin", "password"}, {"user", "1234"}};
int db_size = sizeof(database) / sizeof(database[0]);

int login(const char *username, const char *password) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].username, username) == 0) {
            if (strcmp(database[i].password, password) == 0) {
                printf("Login successful. Redirecting to home page.\n");
                return 1;
            } else {
                printf("Incorrect password.\n");
                return 0;
            }
        }
    }
    printf("Username not found.\n");
    return 0;
}

int main() {
    char username[MAX_USER];
    char password[MAX_PASS];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    login(username, password);

    return 0;
}