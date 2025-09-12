#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

int get_user_count() {
    return sizeof(database) / sizeof(User);
}

void login_page() {
    char input_username[50], input_password[50];

    printf("Enter Username: ");
    scanf("%49s", input_username);
    printf("Enter Password: ");
    scanf("%49s", input_password);

    int user_found = 0;

    for (int i = 0; i < get_user_count(); ++i) {
        if (strcmp(database[i].username, input_username) == 0 &&
            strcmp(database[i].password, input_password) == 0) {
            printf("Login successful! Redirecting to the dashboard...\n");
            user_found = 1;
            break;
        }
    }

    if (!user_found) {
        printf("Invalid credentials. Redirecting back to login page...\n");
        exit(0);
    }
}

int main() {
    while (1) {
        login_page();
        char choice;
        printf("Do you want to log out and try again? (y/n): ");
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            continue;
        } else {
            break;
        }
    }
    
    return 0;
}