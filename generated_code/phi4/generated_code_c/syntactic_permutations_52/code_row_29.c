#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100

void redirectTo(const char *page) {
    printf("Redirecting to %s...\n", page);
}

void do_login(char username[], char password[]) {
    const char correct_username[MAX_USERNAME_LENGTH] = "admin";
    const char correct_password[MAX_PASSWORD_LENGTH] = "password123";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        printf("Login successful! Username set in session: %s\n", username);
        redirectTo("/secret");
    } else {
        printf("Invalid username or password.\n");
    }
}

void show_login_page() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Login Page\n");
    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    do_login(username, password);
}

void show_secret_page() {
    printf("Secret Page\n");
    printf("Secret settings\n");
}

int main() {
    char choice;
    
    while (1) {
        printf("\nIndex Page\n");
        printf("1. Login\n2. Exit\nChoose an option: ");
        
        scanf("%c", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case '1':
                show_login_page();
                break;
            case '2':
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}