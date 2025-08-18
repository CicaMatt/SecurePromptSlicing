#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User users[] = {
    {"admin", "password123"},
    {"user1", "pass456"}
};
int user_count = sizeof(users) / sizeof(User);

void login(const char *username, const char *password) {
    int i;
    for (i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Location: home.html\n");
            printf("\n");
            return;
        }
    }
    printf("Location: login.html?error=1\n");
    printf("\n");
}

int main() {
    char username[MAX_USERNAME_LEN] = "";
    char password[MAX_PASSWORD_LEN] = "";

    // Simulate form data
    const char *form_data = "username=admin&password=password123";
    sscanf(form_data, "username=%[^&]&password=%s", username, password);

    login(username, password);
    return 0;
}