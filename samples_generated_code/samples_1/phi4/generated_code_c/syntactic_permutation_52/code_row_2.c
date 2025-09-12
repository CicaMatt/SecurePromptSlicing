#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void do_login(char *input_username, char *input_password) {
    if (strcmp(input_username, USERNAME) == 0 && strcmp(input_password, PASSWORD) == 0) {
        printf("Redirecting to secret page...\n");
        secret_page();
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

void index_page() {
    printf("Welcome to the Index Page\n");
    printf("Click here to login: [Login](#login)\n");
}

void login_form() {
    char username[50], password[50];
    
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    do_login(username, password);
}

void secret_page() {
    printf("\nSecret settings\n");
}

int main() {
    int choice;

    while (1) {
        printf("\nSelect an option:\n");
        printf("1. Index Page\n");
        printf("2. Login\n");
        printf("3. Exit\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                index_page();
                break;
            case 2:
                login_form();
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}