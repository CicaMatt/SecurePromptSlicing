#include <stdio.h>
#include <string.h>

// Simulate session with a global variable
char username[50] = {0};

void do_login(const char *input_username, const char *input_password) {
    // Hardcoded credentials for demonstration
    if (strcmp(input_username, "admin") == 0 && strcmp(input_password, "password123") == 0) {
        strcpy(username, input_username);
        printf("Redirecting to secret page...\n");
        show_secret_page();
    } else {
        printf("Invalid username or password.\n");
    }
}

void index_page() {
    printf("Welcome! Please <a href='/login'>Login</a> to access the secret settings.\n");
}

void login_page() {
    char input_username[50];
    char input_password[50];

    printf("Enter Username: ");
    scanf("%49s", input_username);
    printf("Enter Password: ");
    scanf("%49s", input_password);

    do_login(input_username, input_password);
}

void show_secret_page() {
    if (strcmp(username, "admin") == 0) {
        printf("Secret settings\n");
    } else {
        printf("Unauthorized access!\n");
        index_page();
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Index Page\n2. Login Page\n3. Exit\n");
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
                printf("Invalid choice.\n");
        }
    }

    return 0;
}