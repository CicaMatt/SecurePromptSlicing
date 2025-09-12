#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS];
int user_count = 0;

void load_users() {
    strcpy(users[user_count].username, "user1");
    strcpy(users[user_count].password, "pass1");
    user_count++;

    strcpy(users[user_count].username, "user2");
    strcpy(users[user_count].password, "pass2");
    user_count++;
}

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    load_users();

    const char *username = "user1";
    const char *password = "pass1";

    if (authenticate(username, password)) {
        redirect("/home.html");
    } else {
        redirect("/login.html");
    }

    return 0;
}