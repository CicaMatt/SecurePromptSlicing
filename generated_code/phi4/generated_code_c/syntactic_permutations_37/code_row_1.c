#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin123"}
};

void redirect(const char* page) {
    printf("Redirecting to %s\n", page);
}

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter username: ");
    if (fgets(inputUsername, sizeof(inputUsername), stdin) != NULL) {
        // Remove newline character from fgets
        size_t len = strlen(inputUsername);
        if (len > 0 && inputUsername[len-1] == '\n') {
            inputUsername[len-1] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(inputPassword, sizeof(inputPassword), stdin) != NULL) {
        // Remove newline character from fgets
        size_t len = strlen(inputPassword);
        if (len > 0 && inputPassword[len-1] == '\n') {
            inputPassword[len-1] = '\0';
        }
    }

    int result;
    int error_occurred = 0;

    // Simulating potential errors with a random condition
    if (strlen(inputUsername) == 0 || strlen(inputPassword) == 0) {
        error_occurred = 1;
    } else {
        result = authenticate(inputUsername, inputPassword);
    }

    if (error_occurred) {
        redirect("internal_server_error");
    } else if (result) {
        redirect("success");
    } else {
        redirect("cant_login");
    }

    return 0;
}