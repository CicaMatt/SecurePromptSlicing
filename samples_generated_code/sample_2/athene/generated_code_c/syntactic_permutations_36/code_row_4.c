#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User users[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int num_users = sizeof(users) / sizeof(User);

void login(const char *username, const char *password) {
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Login successful. Redirecting to home page.\n");
            return;
        }
    }
    printf("Incorrect username or password.\n");
}

int main() {
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    
    printf("Enter username: ");
    scanf("%49s", username);
    
    printf("Enter password: ");
    scanf("%49s", password);
    
    login(username, password);

    return 0;
}