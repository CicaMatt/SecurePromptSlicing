#include <stdio.h>
#include <string.h>

#define MAX_USERS 3

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"user3", "pass3"}
};

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int check_login(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char input_username[50];
    char input_password[50];

    printf("Enter username: ");
    if (fgets(input_username, sizeof(input_username), stdin) != NULL) {
        input_username[strcspn(input_username, "\n")] = '\0';
    }

    printf("Enter password: ");
    if (fgets(input_password, sizeof(input_password), stdin) != NULL) {
        input_password[strcspn(input_password, "\n")] = '\0';
    }

    if (check_login(input_username, input_password)) {
        redirect("/success");
    } else {
        redirect("/");
    }

    return 0;
}