#include <stdio.h>
#include <string.h>

#define MAX_USER 100
#define MAX_PASSWORD 100

typedef struct {
    char username[MAX_USER];
    char password[MAX_PASSWORD];
} User;

User database[] = {
    {"john", "secret"},
    {"jane", "password"},
    // Add more users as needed
};
int db_size = sizeof(database) / sizeof(database[0]);

void login(const char *username, const char *password) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].username, username) == 0) {
            if (strcmp(database[i].password, password) == 0) {
                printf("Login successful. Redirecting to home page.\n");
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
    char username[MAX_USER], password[MAX_PASSWORD];
    
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    login(username, password);

    return 0;
}