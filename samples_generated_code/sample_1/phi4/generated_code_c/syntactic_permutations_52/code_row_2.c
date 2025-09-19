#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void do_login(char *username, char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Login successful. Redirecting to secret page...\n");
        secret_page();
    } else {
        printf("Invalid username or password.\n");
    }
}

void secret_page() {
    printf("Secret settings\n");
}

void login_page() {
    char username[50];
    char password[50];

    printf("Login Page\n");
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    do_login(username, password);
}

void index_page() {
    printf("Index Page\n");
    printf("Click here to [login](#login).\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Index Page\n2. Login Page\n3. Exit\nChoose an option: ");
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