#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

User usersDatabase[] = {
    {"user1@example.com"},
    {"user2@example.com"},
    {"user3@example.com"}
};

int findEmailIndex(const char* email) {
    for (int i = 0; i < sizeof(usersDatabase) / sizeof(usersDatabase[0]); i++) {
        if (strcmp(usersDatabase[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void handleUnsubscribe(const char* email) {
    int index = findEmailIndex(email);
    
    if (index != -1) {
        printf("User with email %s unsubscribed successfully.\n", email);

        for (int i = index; i < sizeof(usersDatabase) / sizeof(usersDatabase[0]) - 1; i++) {
            usersDatabase[i] = usersDatabase[i + 1];
        }
    } else {
        printf("User with email %s is not subscribed to the mailing list.\n", email);
    }
}

int main() {
    char userEmail[MAX_EMAIL_LENGTH];

    printf("Enter email to unsubscribe: ");
    fgets(userEmail, MAX_EMAIL_LENGTH, stdin);

    // Remove newline character from input
    size_t len = strlen(userEmail);
    if (len > 0 && userEmail[len - 1] == '\n') {
        userEmail[len - 1] = '\0';
    }

    handleUnsubscribe(userEmail);

    return 0;
}