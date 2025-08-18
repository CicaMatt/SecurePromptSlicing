#include <stdio.h>
#include <string.h>

#define SESSION_SIZE 256

typedef struct {
    char username[32];
} Session;

void do_login(const char *input_username, const char *input_password) {
    if (strcmp(input_username, "admin") == 0 && strcmp(input_password, "password123") == 0) {
        strcpy(session.username, input_username);
        printf("Redirecting to secret page...\n");
        show_secret_page();
    } else {
        printf("Invalid username or password.\n");
    }
}

void show_index_page() {
    printf("Index Page\n");
    printf("<a href='/login'>Login</a>\n");
}

void show_login_page() {
    char username[32], password[32];
    
    printf("Login Page\n");
    printf("Username: ");
    scanf("%31s", username);
    printf("Password: ");
    scanf("%31s", password);

    do_login(username, password);
}

void show_secret_page() {
    if (session.username[0] != '\0') {
        printf("Secret Settings\n");
    } else {
        printf("Access Denied. Please login.\n");
    }
}

int main() {
    Session session = { .username[0] = '\0' }; // Initialize an empty session
    int choice;

    while (1) {
        printf("\nChoose an option:\n1. Index Page\n2. Login Page\n3. Exit\n> ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                show_index_page();
                break;
            case 2:
                show_login_page();
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}