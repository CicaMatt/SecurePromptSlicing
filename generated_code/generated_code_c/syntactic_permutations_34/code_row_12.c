#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
int check_login(char *, char *);
void dashboard();

int main() {
    // Get username and password from user
    char username[256];
    printf("Enter Username: ");
    scanf("%s", &username);
    getchar();

    char password[256];
    printf("Enter Password: ");
    scanf("%s", &password);
    getchar();

    if (check_login(username, password) == 1) {
        dashboard();
    } else {
        // Invalid login credentials
        main();
    }

    return 0;
}

// Check username and password against database
int check_login(char *username, char *password) {
    // Database with hardcoded usernames and passwords
    const int num_users = 3;
    struct user {
        char username[256];
        char password[256];
    };
    struct user users[num_users] = {{"admin", "pass"}, {"john", "1234"}, {"mary", "qwer"}};

    for (int i = 0; i < num_users; ++i) {
        if ((strcmp(username, users[i].username) == 0) && (strcmp(password, users[i].password) == 0)) {
            return 1;
        }
    }

    return 0;
}

// Display dashboard page
void dashboard() {
    printf("Login successful! Welcome to the dashboard.\n");
}