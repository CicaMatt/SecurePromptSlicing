#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database of users for demonstration purposes.
typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int db_size = 2;

// Function to simulate login process
void login(char *username, char *password) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].username, username) == 0) {
            if (strcmp(database[i].password, password) == 0) {
                printf("Login successful! Redirecting to home page...\n");
                return;
            } else {
                printf("Incorrect password. Please try again.\n");
                return;
            }
        }
    }
    printf("Username does not exist.\n");
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