#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

User usersDatabase[] = {
    {"user1@example.com"},
    {"user2@example.com"},
    {"user3@example.com"}
};

int isSubscribed(const char *email) {
    for (int i = 0; i < sizeof(usersDatabase) / sizeof(User); ++i) {
        if (strcmp(usersDatabase[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribeUser(int index) {
    memmove(&usersDatabase[index], &usersDatabase[index + 1],
            (sizeof(usersDatabase) / sizeof(User) - index - 1) * sizeof(User));
}

int main() {
    char email[MAX_EMAIL_LENGTH];
    printf("Enter email to unsubscribe: ");
    fgets(email, MAX_EMAIL_LENGTH, stdin);
    email[strcspn(email, "\n")] = '\0';

    int index = isSubscribed(email);

    if (index != -1) {
        unsubscribeUser(index);
        printf("%s has been unsubscribed from the mailing list.\n", email);
    } else {
        printf("The user with email %s is not subscribed.\n", email);
    }

    return 0;
}