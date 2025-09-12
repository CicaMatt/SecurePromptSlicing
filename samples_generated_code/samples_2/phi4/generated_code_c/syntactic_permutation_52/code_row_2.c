#include <stdio.h>
#include <string.h>

#define MAX_SESSION_SIZE 1024

typedef struct {
    char username[MAX_SESSION_SIZE];
} Session;

Session session = {0};

void do_login(const char *input_username, const char *input_password) {
    if (strcmp(input_username, "admin") == 0 && strcmp(input_password, "password123") == 0) {
        strcpy(session.username, input_username);
        printf("Redirecting to secret page...\n");
        show_secret_page();
    } else {
        printf("Invalid username or password.\n");
        show_index_page();
    }
}

void show_login_page() {
    printf("Login Page\n");
    printf("Username: admin\n");
    printf("Password: Enter in terminal\n");
    char input_username[50], input_password[50];

    printf("Enter Username: ");
    scanf("%49s", input_username);
    printf("Enter Password: ");
    scanf("%49s", input_password);

    do_login(input_username, input_password);
}

void show_index_page() {
    printf("Index Page\n");
    printf("1. Login\n");
    printf("\nChoose an option:\n");
    
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        show_login_page();
    } else {
        show_index_page();
    }
}

void show_secret_page() {
    printf("Secret Page\n");
    printf("\"Secret settings\"\n");
    printf("Logged in as: %s\n", session.username);
}

int main() {
    show_index_page();
    return 0;
}