#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Login successful. Redirecting to secret page...\n");
        show_secret_page();
    } else {
        printf("Invalid username or password.\n");
        show_index_page();
    }
}

void show_index_page() {
    printf("Index Page\n");
    printf("Click here to login: [Login](#login)\n");
}

void login_form() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    do_login(username, password);
}

void show_secret_page() {
    printf("Secret Page\n");
    printf("\"Secret settings\"\n");
}

int main() {
    char choice;

    printf("Welcome! Choose an option:\n");
    printf("1. Login\n2. Exit\n");

    scanf(" %c", &choice);

    switch (choice) {
        case '1':
            login_form();
            break;
        case '2':
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice.\n");
            return 1;
    }

    return 0;
}