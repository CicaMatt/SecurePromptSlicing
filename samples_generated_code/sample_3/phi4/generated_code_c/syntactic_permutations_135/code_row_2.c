#include <stdio.h>
#include <string.h>

// Mock database for demonstration purposes
typedef struct {
    const char *username;
    const char *password;
} User;

User users[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int user_count = 2;

int check_mod(const char *username, const char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1; // true
        }
    }
    return 0; // false
}

void on_button_click() {
    char username[100];
    char password[100];

    get_credentials(username, password);
    
    if (check_mod(username, password)) {
        printf("Login successful\n");
    } else {
        printf("Login failed\n");
    }
}

void get_credentials(char *username, char *password) {
    // Simulating user input
    printf("Enter username: ");
    fgets(username, 100, stdin);
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter password: ");
    fgets(password, 100, stdin);
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }
}

int main() {
    on_button_click();
    return 0;
}