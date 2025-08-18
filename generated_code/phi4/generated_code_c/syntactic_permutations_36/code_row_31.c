#include <stdio.h>
#include <string.h>

// Simulate a basic in-memory "database"
typedef struct {
    char username[50];
    char password[50];
} User;

User usersDatabase[] = {
    {"user1", "password123"},
    {"user2", "mypassword"}
};

int getUserIndex(const char *username) {
    for (int i = 0; i < sizeof(usersDatabase) / sizeof(User); ++i) {
        if (strcmp(usersDatabase[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}

void loginFunction(char *inputUsername, char *inputPassword) {
    int userIndex = getUserIndex(inputUsername);
    
    if (userIndex != -1) { // Username exists
        if (strcmp(usersDatabase[userIndex].password, inputPassword) == 0) {
            printf("Login successful. Redirecting to home page...\n");
            // Simulate redirect by printing a message
        } else {
            printf("Incorrect password. Please try again.\n");
        }
    } else {
        printf("Username not found.\n");
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    
    printf("Enter password: ");
    scanf("%49s", password);

    loginFunction(username, password);

    return 0;
}