#include <stdio.h>
#include <string.h>

// Function to simulate authentication check for moderators
int auth_mod(const char *name, const char *password, const char *session) {
    // Dummy logic: Assume "admin" with password "mod123" is the moderator
    return strcmp(name, "admin") == 0 && strcmp(password, "mod123") == 0;
}

// Function to handle checking if a user is a moderator
void check_mod(const char *name, const char *password, const char *session) {
    if (auth_mod(name, password, session)) {
        printf("User %s is a moderator.\n", name);
    } else {
        printf("User %s is not a moderator.\n", name);
    }
}

int main() {
    // Simulate a call to check_mod from the URL /check_mod
    const char *name = "admin";
    const char *password = "mod123";
    const char *session = "xyz";

    check_mod(name, password, session);

    return 0;
}