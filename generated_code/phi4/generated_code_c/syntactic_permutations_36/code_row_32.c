#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Simulated database for demonstration purposes.
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "password123"},
    {"admin", "securePass"}
};

int query_database(const char *username) {
    for (size_t i = 0; i < sizeof(users) / sizeof(User); ++i) {
        if (strcmp(users[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}

void login_function(const char *username, const char *password) {
    int user_index = query_database(username);
    
    if (user_index != -1) { // Username exists.
        if (strcmp(users[user_index].password, password) == 0) { 
            printf("Redirecting to home page...\n");
            // Code for redirecting to the home page would go here.
        } else {
            printf("Invalid password. Access denied.\n");
        }
    } else {
        printf("Username not found. Please try again.\n");
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    login_function(username, password);

    return 0;
}