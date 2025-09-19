#include <stdio.h>
#include <string.h>

#define MAX_SESSION_LENGTH 256

char session[MAX_SESSION_LENGTH] = {0};

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        strncpy(session, username, MAX_SESSION_LENGTH - 1);
        printf("Redirecting to secret page...\n");
        display_secret_page();
    } else {
        printf("Invalid credentials. Please try again.\n");
    }
}

void display_index_page() {
    printf("Welcome!\n");
    printf("<a href='login'>Login</a>\n");
}

void display_login_page() {
    char username[50];
    char password[50];

    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    do_login(username, password);
}

void display_secret_page() {
    if (strcmp(session, "admin") == 0) {
        printf("Secret settings\n");
    } else {
        printf("Access denied. Please login.\n");
        display_index_page();
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Index Page\n");
        printf("2. Login Page\n");
        printf("3. Secret Page\n");
        printf("4. Exit\n");

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
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}