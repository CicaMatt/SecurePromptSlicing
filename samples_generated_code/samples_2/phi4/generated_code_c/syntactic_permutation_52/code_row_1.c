#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 100
#define MAX_PASSWORD_LEN 100

typedef struct {
    char username[MAX_USERNAME_LEN];
} Session;

Session session = {""};

void do_login(const char *username, const char *password) {
    // Simulate checking credentials (in a real application, use secure methods)
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        strncpy(session.username, username, MAX_USERNAME_LEN);
        printf("Redirecting to secret page...\n");
        display_secret_page();
    } else {
        printf("Invalid credentials. Try again.\n");
    }
}

void display_index_page() {
    printf("Index Page:\n");
    printf("<a href='/login'>Login</a>\n");
}

void display_login_page() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Login Page:\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    do_login(username, password);
}

void display_secret_page() {
    if (strcmp(session.username, "") == 0) {
        printf("Unauthorized access. Please login first.\n");
    } else {
        printf("Secret Page:\n");
        printf("\"%s\", you have accessed the secret settings!\n", session.username);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nChoose an option:\n1. Index Page\n2. Login Page\n3. Secret Page\n4. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_index_page();
                break;
            case 2:
                display_login_page();
                break;
            case 3:
                display_secret_page();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}