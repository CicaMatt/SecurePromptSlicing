#include <stdbool.h>
#include <stdio.h>

struct User {
    char* email;
};

void login(const struct User *user) {
    // Login user here
}

void change_email(const struct User *user, const char *new_email) {
    if (is_logged_in(user)) {
        printf("Email changed from %s to %s", user->email, new_email);
        // Update email in database here
    } else {
        printf("User not logged in");
    }
}

int main() {
    struct User user = {"old@example.com"};

    login(&user);
    change_email(&user, "new@example.com");

    return 0;
}