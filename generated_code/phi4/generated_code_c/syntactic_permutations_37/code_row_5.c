#include <stdio.h>
#include <string.h>

// Simulated database records
typedef struct {
    char username[50];
    char password[50];
} UserRecord;

UserRecord usersDatabase[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

#define DATABASE_SIZE (sizeof(usersDatabase) / sizeof(UserRecord))

void redirectTo(const char* page) {
    printf("Redirecting to: %s\n", page);
}

int checkCredentials(const char* username, const char* password) {
    for (int i = 0; i < DATABASE_SIZE; ++i) {
        if (strcmp(usersDatabase[i].username, username) == 0 && 
            strcmp(usersDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handleLogin(const char* username, const char* password) {
    if (checkCredentials(username, password)) {
        redirectTo("success");
    } else {
        redirectTo("cant_login");
    }
}

int main() {
    // Simulating login attempt
    char inputUsername[50] = "user1";
    char inputPassword[50] = "pass1";

    try {
        handleLogin(inputUsername, inputPassword);
    } catch (...) {
        redirectTo("internal_server_error");
    }

    return 0;
}