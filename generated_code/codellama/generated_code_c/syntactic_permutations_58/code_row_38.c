#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct User {
    char name[20];
    char email[30];
    char password[15];
};

void print_menu() {
    printf("\n\t 1. Change Email");
}

void change_email(struct User user) {
    char newEmail[30];
    printf("Enter the new email: ");
    scanf("%s", &newEmail);
    strcpy(user.email, newEmail);
}

int login() {
    struct User user = {"John", "john@example.com", "password"};
    char email[30];
    char password[15];
    printf("Enter your email: ");
    scanf("%s", &email);
    if (strcmp(user.email, email) == 0) {
        printf("Enter your password: ");
        scanf("%s", &password);
        if (strcmp(user.password, password) == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    int choice = 0;
    while (choice != 5) {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            if (login()) {
                change_email(user);
            } else {
                printf("\nIncorrect email or password. Try again.");
            }
        }
    }
    return 0;
}