#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int check_credentials(const char *username, const char *password) {
    for (int i = 0; i < sizeof(database) / sizeof(User); i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *page) {
    printf("Redirecting to %s\n", page);
    // In a real web application, you would use HTTP headers for redirection
    if (strcmp(page, "success") == 0) {
        exit(0);
    } else if (strcmp(page, "cant_login") == 0) {
        exit(1);
    } else if (strcmp(page, "internal_server_error") == 0) {
        exit(2);
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%49s", username); // Ensure no buffer overflow

    printf("Enter your password: ");
    scanf("%49s", password); // Ensure no buffer overflow

    if (check_credentials(username, password)) {
        redirect("success");
    } else {
        redirect("cant_login");
    }

    return 0;
}