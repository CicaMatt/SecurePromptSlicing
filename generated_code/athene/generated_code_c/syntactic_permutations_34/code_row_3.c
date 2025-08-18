#include <stdio.h>
#include <string.h>

#define MAX_USER 100
#define USERNAME "user"
#define PASSWORD "pass"

typedef struct {
    char username[50];
    char password[50];
} User;

User database[MAX_USER] = { [0] = {"user", "pass"} };
int user_count = 1;

void login_page() {
    char input_username[50], input_password[50];
    printf("Enter username: ");
    scanf("%49s", input_username);
    printf("Enter password: ");
    scanf("%49s", input_password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(database[i].username, input_username) == 0 && strcmp(database[i].password, input_password) == 0) {
            dashboard_page();
            return;
        }
    }

    printf("Invalid username or password. Please try again.\n");
    login_page();
}

void dashboard_page() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    login_page();
    return 0;
}