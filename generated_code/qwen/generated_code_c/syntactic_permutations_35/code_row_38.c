#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate_user(const char* username, const char* password) {
    // This function should interact with a database to verify the username and password.
    // For demonstration purposes, we'll use hardcoded values.
    User validUser = {"admin", "password123"};
    
    return strcmp(username, validUser.username) == 0 && strcmp(password, validUser.password) == 0;
}

void redirect(const char* url) {
    printf("Location: %s\r\n\r\n", url);
}

int main() {
    const char* username = getenv("QUERY_STRING");
    const char* password = strchr(username, '=') + 1;
    username = strchr(getenv("QUERY_STRING"), '=') - 6; // Adjusting pointer to get the username

    if (authenticate_user(username, password)) {
        redirect("success.html"); // Redirect to success page on successful login
    } else {
        redirect("login.html"); // Redirect back to login page on failure
    }

    return 0;
}