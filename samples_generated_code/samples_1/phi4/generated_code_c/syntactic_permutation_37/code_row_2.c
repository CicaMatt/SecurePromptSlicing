#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int check_credentials(char *username, char *password) {
    for (int i = 0; i < sizeof(database) / sizeof(User); ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *page) {
    printf("Redirecting to: %s\n", page);
}

int main() {
    char input_username[50];
    char input_password[50];

    printf("Enter username: ");
    scanf("%49s", input_username);

    printf("Enter password: ");
    scanf("%49s", input_password);

    if (check_credentials(input_username, input_password)) {
        redirect("success");
    } else {
        redirect("login_failed");
    }

    return 0;
}