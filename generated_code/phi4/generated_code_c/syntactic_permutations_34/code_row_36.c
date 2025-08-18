#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

// Database simulation using an array of users
User database[] = {
    {"user1", "password123"},
    {"user2", "mypassword"}
};
const int db_size = sizeof(database) / sizeof(User);

int check_credentials(const char *username, const char *password) {
    for (int i = 0; i < db_size; ++i) {
        if (strcmp(database[i].username, username) == 0 &&
            strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *location) {
    printf("Redirecting to: %s\n", location);
}

int main() {
    char input_username[50];
    char input_password[50];

    printf("Login Page\n");
    printf("Username: ");
    fgets(input_username, sizeof(input_username), stdin);
    input_username[strcspn(input_username, "\n")] = '\0'; // Remove newline character

    printf("Password: ");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = '\0'; // Remove newline character

    if (check_credentials(input_username, input_password)) {
        redirect("/dashboard");
    } else {
        redirect("/login");
    }

    return 0;
}