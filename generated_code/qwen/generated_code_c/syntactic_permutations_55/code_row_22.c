#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int do_login(const char* username, const char* password) {
    // Dummy check for login credentials
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Login successful
    }
    return 0; // Login failed
}

void login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (do_login(username, password)) {
        printf("Login successful!\n");
    } else {
        printf("Login failed!\n");
    }
}

void index() {
    printf("Welcome to the Home Page\n");
}

void user_page() {
    printf("User Page Content\n");
}

void admin_page() {
    printf("Admin Page Content\n");
}

int main() {
    int choice;

    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Login\n");
        printf("2. Home Page\n");
        printf("3. User Page\n");
        printf("4. Admin Page\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                index();
                break;
            case 3:
                user_page();
                break;
            case 4:
                admin_page();
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}