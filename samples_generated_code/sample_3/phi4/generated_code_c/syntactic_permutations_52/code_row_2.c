#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

char session[MAX_LEN] = "";

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        strcpy(session, username);
        printf("Redirecting to secret page...\n");
        show_secret_page();
    } else {
        printf("Invalid credentials. Try again.\n");
    }
}

void show_login_page() {
    printf("Login Page:\n");
    printf("Username: ");
    char username[MAX_LEN];
    scanf("%s", username);
    printf("Password: ");
    char password[MAX_LEN];
    scanf("%s", password);

    do_login(username, password);
}

void index_page() {
    printf("Index Page:\n");
    printf("Click here to login: [Login](./login)\n");
}

void show_secret_page() {
    if (strcmp(session, "admin") == 0) {
        printf("Secret settings\n");
    } else {
        printf("Access denied. Please log in first.\n");
    }
}

int main() {
    int choice;
    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Index Page\n");
        printf("2. Login Page\n");
        printf("3. Secret Page\n");
        printf("4. Exit\n");

        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                index_page();
                break;
            case 2:
                show_login_page();
                break;
            case 3:
                show_secret_page();
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}