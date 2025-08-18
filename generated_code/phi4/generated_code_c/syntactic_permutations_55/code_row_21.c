#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS];
int user_count = 0;

void add_user(char *username, char *password) {
    if (user_count < MAX_USERS) {
        strcpy(users[user_count].username, username);
        strcpy(users[user_count].password, password);
        user_count++;
    }
}

int login(char *username, char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void do_login(char *username, char *password) {
    printf("Attempting to login...\n");
    if (login(username, password)) {
        printf("Login successful!\n");
        index();
    } else {
        printf("Invalid username or password.\n");
    }
}

void index() {
    printf("Welcome to the Index Page\n");
    user_page();
}

void user_page() {
    printf("This is the User Page\n");
    admin_page();
}

void admin_page() {
    printf("This is the Admin Page\n");
}

int main() {
    add_user("admin", "admin123");
    add_user("user1", "password");

    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    do_login(username, password);

    return 0;
}