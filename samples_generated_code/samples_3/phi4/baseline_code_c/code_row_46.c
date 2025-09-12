#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
} Session;

Session session = { .username[0] = '\0' };

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int do_login(const char *input_username, const char *input_password) {
    const char correct_username[] = "admin";
    const char correct_password[] = "password";

    if (strcmp(input_username, correct_username) == 0 && strcmp(input_password, correct_password) == 0) {
        strncpy(session.username, input_username, MAX_USERNAME_LENGTH);
        redirect("/secret");
        return 1;
    }
    printf("Invalid username or password.\n");
    return 0;
}

void show_login_page() {
    printf("Login Page\n");
    printf("Username: ");
    char username[MAX_USERNAME_LENGTH];
    scanf("%49s", username);

    printf("Password: ");
    char password[MAX_PASSWORD_LENGTH];
    scanf("%49s", password);

    do_login(username, password);
}

void show_index_page() {
    printf("Index Page\n");
    printf("Click here to login: /login\n");
}

void show_secret_page() {
    if (strcmp(session.username, "") == 0) {
        redirect("/login");
    } else {
        printf("Secret settings\n");
    }
}

int main() {
    int choice;
    do {
        printf("\n1. Index Page\n2. Login Page\n3. Secret Page\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                show_index_page();
                break;
            case 2:
                show_login_page();
                break;
            case 3:
                show_secret_page();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}