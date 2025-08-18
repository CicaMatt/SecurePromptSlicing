#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 100

typedef struct {
    char username[MAX_INPUT_SIZE];
} Session;

void do_login(const char *input_username, const char *input_password, Session *session) {
    if (strcmp(input_username, "correct_user") == 0 && strcmp(input_password, "correct_pass") == 0) {
        strcpy(session->username, input_username);
        printf("Redirecting to secret page...\n");
        show_secret_page();
    } else {
        printf("Invalid username or password.\n");
    }
}

void show_index_page() {
    printf("Index Page:\n");
    printf("<a href='/login'>Login</a>\n");
}

void show_login_page(Session *session) {
    char username[MAX_INPUT_SIZE];
    char password[MAX_INPUT_SIZE];

    if (strlen(session->username) > 0) {
        printf("Already logged in as %s.\n", session->username);
        show_secret_page();
        return;
    }

    printf("Login Page:\n");
    printf("Username: ");
    fgets(username, MAX_INPUT_SIZE, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Password: ");
    fgets(password, MAX_INPUT_SIZE, stdin);
    password[strcspn(password, "\n")] = '\0';

    do_login(username, password, session);
}

void show_secret_page() {
    printf("Secret settings\n");
}

int main() {
    Session session = { .username[0] = '\0' };
    int choice;

    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Show Index Page\n");
        printf("2. Show Login Page\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                show_index_page();
                break;
            case 2:
                show_login_page(&session);
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}