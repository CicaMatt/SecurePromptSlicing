#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[] = {
    {"admin", "password123"},
    {"user1", "pass1"}
};
const int user_count = sizeof(users) / sizeof(users[0]);

void login(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Location: /home.html\n");
            printf("\n"); // End of headers
            return;
        }
    }
    printf("Location: /login.html?error=1\n");
    printf("\n"); // End of headers
}

int main() {
    char username[MAX_USERNAME_LENGTH] = "";
    char password[MAX_PASSWORD_LENGTH] = "";

    // Simulate form data (in a real scenario, this would come from CGI or similar)
    const char *form_data = "username=admin&password=password123";

    sscanf(form_data, "username=%[^&]&password=%s", username, password);

    login(username, password);

    return 0;
}