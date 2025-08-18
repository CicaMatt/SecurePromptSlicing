#include <stdio.h>
#include <string.h>

// Define a structure for user credentials
typedef struct {
    char username[50];
    char password[50];
} User;

// Sample database of users
User usersDatabase[] = {
    {"user1", "password123"},
    {"user2", "mypassword"},
    {"admin", "adminpass"}
};

// Total number of users in the database
#define DATABASE_SIZE (sizeof(usersDatabase) / sizeof(usersDatabase[0]))

void redirectTo(const char* page) {
    printf("Redirecting to: %s\n", page);
}

int authenticateUser(const char* username, const char* password) {
    for (int i = 0; i < DATABASE_SIZE; ++i) {
        if (strcmp(usersDatabase[i].username, username) == 0 &&
            strcmp(usersDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginProcess(const char* username, const char* password) {
    int result = authenticateUser(username, password);
    if (result > 0) {
        redirectTo("success");
    } else {
        redirectTo("cant_login");
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    loginProcess(username, password);
    
    return 0;
}