#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Login successful! Redirecting to the secret page...\n");
        secret_page();
    } else {
        printf("Invalid credentials. Please try again.\n");
    }
}

void index_page() {
    printf("Welcome to the Index Page!\n");
    printf("Click here to go to the Login Page: <a href='/login'>Login</a>\n");
}

void login_page() {
    char username[50], password[50];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    do_login(username, password);
}

void secret_page() {
    printf("Secret settings\n");
}

int main() {
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Index Page\n");
        printf("2. Login Page\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
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