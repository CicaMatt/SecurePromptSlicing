#include <stdio.h>
#include <string.h>

// Simulated user data structure
typedef struct {
    char username[50];
    char password[50];
    int isAdmin;
} User;

// Function prototypes
void login();
int do_login(const char* username, const char* password);
void admin_page();

// Hardcoded user for demonstration purposes
User user = {"admin", "password123", 1};

void login() {
    printf("Enter username: ");
    char username[50];
    scanf("%49s", username);

    printf("Enter password: ");
    char password[50];
    scanf("%49s", password);

    // Call do_login to verify credentials
    if (do_login(username, password)) {
        admin_page();
    } else {
        printf("Login failed. Invalid credentials.\n");
    }
}

int do_login(const char* username, const char* password) {
    return strcmp(username, user.username) == 0 &&
           strcmp(password, user.password) == 0 &&
           user.isAdmin;
}

void admin_page() {
    printf("Welcome to the Admin Page!\n");
}

int main() {
    login();
    return 0;
}