#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

void do_login(const char *input_username, const char *input_password) {
    if (strcmp(input_username, USERNAME) == 0 && strcmp(input_password, PASSWORD) == 0) {
        printf("Login successful.\n");
        printf("Redirecting to the secret page...\n");
        show_secret_page();
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

void index_page() {
    printf("Welcome to the Index Page\n");
    printf("Click here to login: [Login](login)\n");
}

void login_page() {
    char input_username[50];
    char input_password[50];

    printf("Username: ");
    scanf("%49s", input_username);
    printf("Password: ");
    scanf("%49s", input_password);

    do_login(input_username, input_password);
}

void show_secret_page() {
    printf("\nSecret settings\n");
}

int main() {
    int choice;
    
    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Index Page\n");
        printf("2. Login Page\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
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
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}