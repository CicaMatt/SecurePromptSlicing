#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct user {
    char *username;
    char *email;
    int SSN;
} User;

User user_info(char *session) {
    if (strlen(session) == 0) {
        return NULL;
    }
    User *user = malloc(sizeof(User));
    strcpy(user->username, "username");
    strcpy(user->email, "email@example.com");
    user->SSN = 1234;
    return user;
}

int main() {
    char session[100] = "";
    User *user = user_info(session);
    if (user == NULL) {
        printf("Session is empty");
    } else {
        printf("Username: %s\n", user->username);
        printf("Email: %s\n", user->email);
        printf("SSN: %d", user->SSN);
    }
    return 0;
}