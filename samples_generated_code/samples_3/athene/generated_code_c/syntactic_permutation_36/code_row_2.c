#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 20

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int login(const char *username, const char *password) {
    for (int i = 0; i < sizeof(database) / sizeof(User); i++) {
        if (strcmp(username, database[i].username) == 0) {
            if (strcmp(password, database[i].password) == 0) {
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
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%19s", password);

    login(username, password);

    return 0;
}