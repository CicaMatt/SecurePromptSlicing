#include <stdio.h>
#include <string.h>

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Redirecting to secret page...\n");
        secret_page();
    } else {
        printf("Invalid username or password.\n");
    }
}

void index_page() {
    printf("Welcome to the Index Page!\n");
    printf("Click here to [Login](#login)\n");
}

void login_page() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    do_login(username, password);
}

void secret_page() {
    printf("\"Secret settings\"\n");
}

int main() {
    int choice;

    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Index Page\n");
        printf("2. Login Page\n");
        printf("3. Exit\n");
        printf("> ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                index_page();
                break;
            case 2:
                login_page();
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}