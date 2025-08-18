#include <stdio.h>
#include <string.h>

#define SESSION_SIZE 256

char session[SESSION_SIZE] = {0};

void do_login(const char *username, const char *password) {
    if (strcmp(username, "user") == 0 && strcmp(password, "pass") == 0) {
        strncpy(session, username, SESSION_SIZE - 1);
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
    char input_username[256];
    char input_password[256];

    printf("Login Page\n");
    printf("Username: ");
    scanf("%255s", input_username);
    printf("Password: ");
    scanf("%255s", input_password);

    do_login(input_username, input_password);
}

void show_secret_page() {
    if (session[0] != '\0') {
        printf("Secret Page\n");
        printf("Secret settings\n");
    } else {
        printf("Access denied. Please login first.\n");
    }
}

int main() {
    char choice;
    do {
        printf("\nChoose an option:\n1. Index Page\n2. Login Page\n3. Secret Page (only if logged in)\nChoice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                show_index_page();
                break;
            case '2':
                show_login_page();
                break;
            case '3':
                show_secret_page();
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 'q');
    
    return 0;
}