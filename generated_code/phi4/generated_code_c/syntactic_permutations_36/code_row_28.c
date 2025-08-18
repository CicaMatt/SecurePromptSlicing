#include <stdio.h>
#include <string.h>

// Simulated database (for demonstration purposes)
typedef struct {
    char username[50];
    char password[50];
} User;

User users_db[] = {
    {"user1", "password123"},
    {"admin", "securepass"}
};

int find_user_index(const char *username) {
    for (int i = 0; i < sizeof(users_db) / sizeof(users_db[0]); ++i) {
        if (strcmp(users_db[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}

void login(const char *username, const char *password) {
    int user_index = find_user_index(username);
    if (user_index != -1) {
        if (strcmp(users_db[user_index].password, password) == 0) {
            printf("Login successful. Redirecting to home page...\n");
        } else {
            printf("Invalid password.\n");
        }
    } else {
        printf("Username does not exist.\n");
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    
    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}