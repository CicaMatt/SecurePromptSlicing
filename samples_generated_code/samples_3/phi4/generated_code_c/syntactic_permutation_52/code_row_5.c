#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void do_login(const char *input_username, const char *input_password) {
    if (strcmp(input_username, USERNAME) == 0 && strcmp(input_password, PASSWORD) == 0) {
        printf("Redirecting to secret page...\n");
        secret_page();
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

void index_page() {
    printf("Welcome! <a href='/login'>Login</a>\n");
}

void login_page() {
    char username[50], password[50];

    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    do_login(username, password);
}

void secret_page() {
    printf("Secret settings\n");
}

int main() {
    index_page();

    char choice;
    printf("\nDo you want to login? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        login_page();
    } else {
        printf("Exiting...\n");
    }

    return 0;
}