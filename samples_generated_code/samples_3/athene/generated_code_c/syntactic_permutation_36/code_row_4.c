#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {{"john", "1234"}, {"jane", "5678"}};
int db_size = sizeof(database) / sizeof(database[0]);

void login(const char *username, const char *password) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].username, username) == 0) {
            if (strcmp(database[i].password, password) == 0) {
                printf("Redirecting to home page...\n");
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
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    login(username, password);
    return 0;
}