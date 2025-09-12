#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 100
#define MAX_PASSWORD_LEN 100

typedef struct {
    char username[MAX_USERNAME_LEN];
} Session;

Session session;

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        strcpy(session.username, username);
        printf("Redirecting to secret page...\n");
        secret_page();
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

void index_page() {
    printf("Index Page\n");
    printf("Click here to login: <a href='login'>Login</a>\n");
}

void login_page() {
    printf("Login Page\n");
    printf("Username: ");
    char username[MAX_USERNAME_LEN];
    scanf("%s", username);
    printf("Password: ");
    char password[MAX_PASSWORD_LEN];
    scanf("%s", password);
    
    do_login(username, password);
}

void secret_page() {
    if (strcmp(session.username, "") == 0) {
        printf("Unauthorized access. Please login first.\n");
    } else {
        printf("Secret settings\n");
        printf("Welcome, %s!\n", session.username);
    }
}

int main() {
    char choice;
    
    while (1) {
        printf("\nEnter 'i' for Index Page, 'l' for Login Page, or 'q' to Quit: ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'i':
                index_page();
                break;
            case 'l':
                login_page();
                break;
            case 'q':
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}