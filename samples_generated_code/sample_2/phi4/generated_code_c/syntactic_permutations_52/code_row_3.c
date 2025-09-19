#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
} Session;

Session session;
int isLoggedIn = 0;

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        strcpy(session.username, username);
        isLoggedIn = 1;
        printf("Redirecting to secret page...\n");
        show_secret_page();
    } else {
        printf("Invalid credentials. Please try again.\n");
    }
}

void show_login_page() {
    printf("Login Page\n");
    printf("Username: ");
    char username[MAX_USERNAME_LENGTH];
    scanf("%s", username);
    printf("Password: ");
    char password[MAX_PASSWORD_LENGTH];
    scanf("%s", password);

    do_login(username, password);
}

void show_index_page() {
    printf("Index Page\n");
    printf("Click here to login: [Login](login)\n");
}

void show_secret_page() {
    if (isLoggedIn) {
        printf("Secret settings page\n");
    } else {
        printf("You are not logged in. Please log in first.\n");
    }
}

int main() {
    int choice;

    do {
        printf("\n1: Index Page\n2: Login Page\n3: Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                show_index_page();
                break;
            case 2:
                if (!isLoggedIn) {
                    show_login_page();
                } else {
                    printf("You are already logged in.\n");
                }
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);

    return 0;
}