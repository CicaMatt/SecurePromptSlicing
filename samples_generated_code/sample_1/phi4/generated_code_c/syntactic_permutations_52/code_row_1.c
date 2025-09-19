#include <stdio.h>
#include <string.h>

#define SESSION_KEY "username"
#define USERNAME "admin"
#define PASSWORD "password"

typedef struct {
    char username[50];
} Session;

void start_session(Session *session) {
    printf("Session started\n");
}

void set_session_value(Session *session, const char *key, const char *value) {
    if (strcmp(key, SESSION_KEY) == 0) {
        strcpy(session->username, value);
    }
}

int get_session_value(const Session *session, const char *key) {
    if (strcmp(key, SESSION_KEY) == 0) {
        return session->username[0] != '\0';
    }
    return 0;
}

void do_login(Session *session, const char *input_username, const char *input_password) {
    if (strcmp(input_username, USERNAME) == 0 && strcmp(input_password, PASSWORD) == 0) {
        set_session_value(session, SESSION_KEY, input_username);
        printf("Redirecting to secret page...\n");
        secret_page();
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

void index_page() {
    printf("Welcome to the Index Page\n");
    printf("Please login: <a href='/login'>Login</a>\n");
}

void login_page(Session *session) {
    char input_username[50];
    char input_password[50];

    printf("Username: ");
    scanf("%s", input_username);
    printf("Password: ");
    scanf("%s", input_password);

    do_login(session, input_username, input_password);
}

void secret_page() {
    if (get_session_value(NULL, SESSION_KEY)) {
        printf("Secret settings\n");
    } else {
        printf("Unauthorized access. Redirecting to login...\n");
        index_page();
    }
}

int main() {
    Session session;
    start_session(&session);

    int choice;

    do {
        printf("\n1: Index Page\n2: Login Page\n3: Secret Page (Direct)\n0: Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                index_page();
                break;
            case 2:
                login_page(&session);
                break;
            case 3:
                secret_page();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}