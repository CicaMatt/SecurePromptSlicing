#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

int check_user_in_db(const char *username, const char *password) {
    // Simulated database with one user for demonstration purposes.
    User users[] = {
        {"user1", "pass1"},
        {"user2", "pass2"}
    };
    
    int num_users = sizeof(users) / sizeof(User);
    for (int i = 0; i < num_users; ++i) {
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
    // Simulate form input
    char username[50] = "user1";
    char password[50] = "pass1";

    if (check_user_in_db(username, password)) {
        redirect("/home.html");
    } else {
        redirect("/login.html");
    }

    return 0;
}