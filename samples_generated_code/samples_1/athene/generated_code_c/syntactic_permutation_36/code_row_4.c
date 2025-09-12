#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User users[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

int num_users = sizeof(users) / sizeof(users[0]);

void login(const char *username, const char *password) {
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful. Redirecting to home page.\n");
            return;
        }
    }
    printf("Incorrect username or password.\n");
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    scanf("%49s", username);
    
    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}