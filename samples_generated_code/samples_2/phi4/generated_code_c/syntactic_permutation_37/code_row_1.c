#include <stdio.h>
#include <string.h>

// Mock database for demonstration purposes
typedef struct {
    char username[50];
    char password[50];
} User;

User usersDatabase[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

#define NUM_USERS (sizeof(usersDatabase) / sizeof(usersDatabase[0]))

// Function to simulate redirection
void redirect(const char* page) {
    printf("Redirecting to: %s\n", page);
}

int authenticate(char* username, char* password) {
    for (int i = 0; i < NUM_USERS; ++i) {
        if (strcmp(usersDatabase[i].username, username) == 0 &&
            strcmp(usersDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginPage() {
    char username[50];
    char password[50];

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
    try {
        loginPage();
    } catch (...) {
        redirect("internal_server_error");
    }

    return 0;
}