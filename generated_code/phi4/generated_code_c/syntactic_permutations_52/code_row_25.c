#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN + 1];
} Session;

void do_login(const char *username, const char *password, Session *session) {
    if (strcmp(username, "user") == 0 && strcmp(password, "pass") == 0) {
        strncpy(session->username, username, MAX_USERNAME_LEN);
        printf("Redirecting to simple page...\n");
        show_simple_page();
    } else {
        printf("Invalid credentials. Please try again.\n");
    }
}

void show_login_page() {
    char username[MAX_USERNAME_LEN + 1];
    char password[MAX_PASSWORD_LEN + 1];

    printf("Login Page\n");
    printf("Username: ");
    scanf("%50s", username);
    printf("Password: ");
    scanf("%50s", password);

    Session session;
    do_login(username, password, &session);
}

void show_simple_page() {
    printf("\nSimple Page\n");
    printf("<a href='login.html'>Login</a>\n");

    if (strlen(session.username) > 0) {
        printf("Welcome, %s! <a href='secret.html'>Secret Settings</a>\n", session.username);
    }
}

void show_secret_page() {
    printf("\nSecret Page\n");
    printf("\"Secret settings\"\n");
}

int main() {
    Session session = { .username[0] = '\0' };

    int choice;
    do {
        printf("\n1. Login\n2. Simple Page\n3. Secret Page (requires login)\n4. Exit\nChoose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                show_login_page();
                break;
            case 2:
                show_simple_page();
                break;
            case 3:
                if (strlen(session.username) > 0) {
                    show_secret_page();
                } else {
                    printf("You need to login first.\n");
                }
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