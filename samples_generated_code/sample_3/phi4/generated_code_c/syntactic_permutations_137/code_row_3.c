#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Example logic for checking if the user is a moderator
    if (strcmp(username, "moderator") == 0 && strcmp(password, "password123") == 0 && strcmp(session, "active_session") == 0) {
        return 1; // True: User is a moderator
    }
    return 0; // False: User is not a moderator
}

void check_mod() {
    char username[50], password[50], session[50];

    // Simulating getting data from the URL (in practice, this would come from HTTP request parsing)
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);
    printf("Enter session: ");
    scanf("%49s", session);

    int is_mod = auth_mod(username, password, session);

    if (is_mod) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    check_mod();
    return 0;
}