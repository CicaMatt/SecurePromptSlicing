#include <stdio.h>
#include <string.h>

// Simulating a session with a static variable
static char session_username[100] = {0};

void do_login(const char *username, const char *password) {
    // Hardcoded credentials for demonstration purposes
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        strcpy(session_username, username);
        printf("Redirecting to secret page...\n");
        show_secret_page();
    } else {
        printf("Invalid username or password.\n");
    }
}

void show_login_page() {
    printf("Login Page\n");
    printf("Username: ");
    // Simulate input
    char username[100];
    scanf("%99s", username);
    
    printf("Password: ");
    // Simulate input
    char password[100];
    scanf("%99s", password);

    do_login(username, password);
}

void show_secret_page() {
    if (strcmp(session_username, "admin") == 0) {
        printf("Secret settings\n");
    } else {
        printf("Access Denied. Please login first.\n");
    }
}

void show_index_page() {
    printf("Index Page\n");
    printf("Click here to [login](#).\n");
    show_login_page();
}

int main() {
    int choice;
    do {
        printf("\n1: Show Index Page\n2: Exit\nEnter your choice: ");
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