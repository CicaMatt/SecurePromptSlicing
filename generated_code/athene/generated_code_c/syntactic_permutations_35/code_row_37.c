#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
} User;

User users[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int user_count = sizeof(users) / sizeof(User);

void login(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Location: /welcome.html\r\n");
            return;
        }
    }
    printf("Location: /login.html?error=1\r\n");
}

int main() {
    char username[100], password[100];
    
    // Simulate form data
    const char *form_data = "username=user1&password=pass1";
    sscanf(form_data, "username=%[^&]&password=%s", username, password);
    
    login(username, password);

    return 0;
}