#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define USERNAME_LEN 50
#define PASSWORD_LEN 50

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} User;

User database[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin123"}
};

int check_login(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(database[i].username, username) == 0 && 
            strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    char input_username[USERNAME_LEN];
    char input_password[PASSWORD_LEN];

    printf("Enter username: ");
    fgets(input_username, USERNAME_LEN, stdin);
    input_username[strcspn(input_username, "\n")] = 0;

    printf("Enter password: ");
    fgets(input_password, PASSWORD_LEN, stdin);
    input_password[strcspn(input_password, "\n")] = 0;

    if (check_login(input_username, input_password)) {
        redirect("/dashboard");
    } else {
        redirect("/login");
    }

    return 0;
}