#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

bool check_credentials(const char *username, const char *password) {
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void simulate_form_input(char *username, char *password) {
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
}

bool check_mod() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    
    simulate_form_input(username, password);
    
    return check_credentials(username, password);
}

int main() {
    if (check_mod()) {
        printf("Login successful.\n");
    } else {
        printf("Invalid username or password.\n");
    }
    return 0;
}