#include <stdio.h>
#include <string.h>

#define MAX_USERS 5
#define USERNAME_LEN 50
#define PASSWORD_LEN 50

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} User;

User database[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin123"},
    {"guest", "guest"},
    {"test", "testpass"}
};

void redirect(const char* page) {
    printf("Redirecting to: %s\n", page);
}

int authenticate(char username[], char password[]) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(database[i].username, username) == 0 &&
            strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        redirect("success");
    } else {
        redirect("cant_login");
    }
}

int main() {
    login_page();
    return 0;
}