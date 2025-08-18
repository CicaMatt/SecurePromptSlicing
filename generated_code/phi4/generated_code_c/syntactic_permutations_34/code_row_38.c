#include <stdio.h>
#include <string.h>

// Simulated database
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

int check_credentials(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users) / sizeof(User); ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (check_credentials(username, password)) {
        printf("Login successful! Redirecting to dashboard...\n");
    } else {
        printf("Invalid credentials. Please try again.\n");
    }
}

void main_menu() {
    int choice;
    do {
        printf("\nMain Menu:\n");
        printf("1. Login\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 2);
}

int main() {
    main_menu();
    return 0;
}