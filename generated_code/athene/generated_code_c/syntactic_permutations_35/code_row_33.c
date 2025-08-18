#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
} User;

User users[] = {
    {"admin", "123456"},
    {"user", "password"}
};

#define NUM_USERS (sizeof(users) / sizeof(User))

void login(const char *username, const char *password) {
    int i;
    for (i = 0; i < NUM_USERS; ++i) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Location: /home.html\r\n");
            printf("\r\n");
            return;
        }
    }
    printf("Location: /login.html?error=1\r\n");
    printf("\r\n");
}

int main() {
    char username[256] = "";
    char password[256] = "";

    // Simulate reading from form data
    const char *form_data = "username=admin&password=123456";
    sscanf(form_data, "username=%[^&]&password=%s", username, password);

    login(username, password);
    return 0;
}