#include <stdio.h>
#include <string.h>

// Simulated session storage (for demonstration purposes)
typedef struct {
    char username[50];
} Session;

Session current_session;

void do_login(const char *username, const char *password) {
    if (strcmp(username, "correctUser") == 0 && strcmp(password, "correctPass") == 0) {
        strcpy(current_session.username, username);
        printf("Redirecting to secret page...\n");
        secret_page();
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

void index_page() {
    printf("Index Page\n");
    printf("Click here to login: [Login](login)\n");
}

void login_page() {
    char username[50];
    char password[50];

    printf("Login Page\nUsername: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    do_login(username, password);
}

void secret_page() {
    if (strlen(current_session.username) > 0) {
        printf("Secret settings\nWelcome %s!\n", current_session.username);
    } else {
        printf("Access Denied. Please login first.\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Index Page\n");
        printf("2. Login Page\n");
        printf("3. Secret Page (only if logged in)\n");
        printf("4. Exit\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                index_page();
                break;
            case 2:
                login_page();
                break;
            case 3:
                secret_page();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}