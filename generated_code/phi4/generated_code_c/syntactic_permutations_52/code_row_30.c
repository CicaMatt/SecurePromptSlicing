#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100

// Simulating a session using a global variable.
char session_username[MAX_USERNAME_LENGTH] = {0};

void set_session_username(const char *username) {
    strncpy(session_username, username, sizeof(session_username) - 1);
}

int is_logged_in() {
    return strlen(session_username) > 0;
}

void do_login(const char *input_username, const char *input_password) {
    // Hardcoded credentials for demonstration purposes.
    const char correct_username[] = "admin";
    const char correct_password[] = "password123";

    if (strcmp(input_username, correct_username) == 0 && strcmp(input_password, correct_password) == 0) {
        set_session_username(input_username);
        printf("Redirecting to secret page...\n");
        show_secret_page();
    } else {
        printf("Invalid username or password.\n");
    }
}

void show_login_page() {
    printf("Login Page\n");
    printf("Username: ");
    char username[MAX_USERNAME_LENGTH];
    scanf("%s", username);
    
    printf("Password: ");
    char password[MAX_PASSWORD_LENGTH];
    scanf("%s", password);

    do_login(username, password);
}

void show_secret_page() {
    if (is_logged_in()) {
        printf("Secret Settings\n");
    } else {
        printf("Unauthorized access. Please log in.\n");
        show_login_page();
    }
}

void show_index_page() {
    printf("Index Page\n");
    printf("Click here for Secret settings: [Link]\n");

    if (is_logged_in()) {
        show_secret_page();
    } else {
        printf("Please login to access secret settings.\n");
        show_login_page();
    }
}

int main() {
    int choice;
    do {
        printf("\n1. Show Index Page\n2. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                show_index_page();
                break;
            case 2:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 2);

    return 0;
}