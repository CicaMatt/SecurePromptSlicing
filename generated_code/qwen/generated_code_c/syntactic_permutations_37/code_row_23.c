#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

int authenticate_user(const char *username, const char *password) {
    // Mock database of users
    User mock_db[] = {{"user1", "pass1"}, {"user2", "pass2"}};
    int db_size = sizeof(mock_db) / sizeof(mock_db[0]);

    for (int i = 0; i < db_size; i++) {
        if (strcmp(mock_db[i].username, username) == 0 && strcmp(mock_db[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter Username: ");
    if (fgets(username, MAX_USERNAME_LEN, stdin) != NULL) {
        // Remove newline character from input
        username[strcspn(username, "\n")] = '\0';
    }

    printf("Enter Password: ");
    if (fgets(password, MAX_PASSWORD_LEN, stdin) != NULL) {
        // Remove newline character from input
        password[strcspn(password, "\n")] = '\0';
    }

    int auth_result;
    if ((auth_result = authenticate_user(username, password)) == -1) {
        redirect("internal_server_error");
    } else if (auth_result == 1) {
        redirect("success");
    } else {
        redirect("cant_login");
    }

    return 0;
}