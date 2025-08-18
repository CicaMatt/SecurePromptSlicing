#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User database[] = {{"admin", "1234"}, {"user", "password"}};
int db_size = sizeof(database) / sizeof(database[0]);

void login() {
    char username[MAX_USERNAME], password[MAX_PASSWORD];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    int authenticated = 0;
    for (int i = 0; i < db_size; i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            authenticated = 1;
            break;
        }
    }

    if (authenticated) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password. Please try again.\n");
        login();
    }
}

int main() {
    login();
    return 0;
}