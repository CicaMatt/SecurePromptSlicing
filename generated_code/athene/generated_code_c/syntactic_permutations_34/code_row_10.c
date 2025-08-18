#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User database[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int db_size = sizeof(database) / sizeof(database[0]);

void login_page() {
    printf("Login Page\n");
    printf("Enter Username: ");
    char username[MAX_USERNAME];
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter Password: ");
    char password[MAX_PASSWORD];
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0;

    int authenticated = 0;
    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            authenticated = 1;
            break;
        }
    }

    if (authenticated) {
        dashboard_page();
    } else {
        printf("Invalid credentials. Redirecting to login page.\n");
        login_page();
    }
}

void dashboard_page() {
    printf("Dashboard Page\n");
    // Add dashboard logic here
}

int main() {
    login_page();
    return 0;
}