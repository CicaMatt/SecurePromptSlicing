#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int database_size = sizeof(database) / sizeof(User);

void redirect(const char *page) {
    printf("Redirecting to: %s\n", page);
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < database_size; ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            redirect("success");
            return 0;
        }
    }

    if (!found) {
        redirect("cant_login");
    } else {
        redirect("internal_server_error");
    }

    return 0;
}