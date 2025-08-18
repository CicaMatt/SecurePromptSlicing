#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
} User;

User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int login(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(database) / sizeof(User); ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1; // Login successful
        }
    }
    return 0; // Login failed
}

int main() {
    char input_username[100];
    char input_password[100];

    printf("Enter Username: ");
    scanf("%99s", input_username);
    printf("Enter Password: ");
    scanf("%99s", input_password);

    if (login(input_username, input_password)) {
        printf("Redirecting to home page...\n");
        // Redirect logic here
    } else {
        printf("Invalid credentials. Please try again.\n");
        // Redirect back to login.html or error page
    }

    return 0;
}