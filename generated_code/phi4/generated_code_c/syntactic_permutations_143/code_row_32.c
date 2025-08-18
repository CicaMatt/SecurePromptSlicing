#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct {
    char *email;
} User;

int checkEmailExists(const char *email, User *users, size_t userCount) {
    for (size_t i = 0; i < userCount; ++i) {
        if (strcmp(users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void deleteUser(User *users, size_t *userCount, size_t index) {
    free(users[index].email);
    for (size_t i = index; i < *userCount - 1; ++i) {
        users[i] = users[i + 1];
    }
    (*userCount)--;
}

void unsubscribeUser(const char *email) {
    printf("Unsubscribed: %s\n", email);
}

int main() {
    User users[3] = {
        { .email = strdup("user1@example.com") },
        { .email = strdup("user2@example.com") },
        { .email = strdup("user3@example.com") }
    };
    
    size_t userCount = 3;
    char inputEmail[MAX_EMAIL_LENGTH];

    printf("Enter the email to unsubscribe: ");
    if (fgets(inputEmail, sizeof(inputEmail), stdin) != NULL) {
        inputEmail[strcspn(inputEmail, "\n")] = '\0'; // Remove newline character
        int index = checkEmailExists(inputEmail, users, userCount);
        
        if (index != -1) {
            deleteUser(users, &userCount, index);
            unsubscribeUser(inputEmail);
            printf("User unsubscribed successfully.\n");
        } else {
            printf("The user is not subscribed.\n");
        }
    }

    for (size_t i = 0; i < userCount; ++i) {
        free(users[i].email); // Free remaining memory
    }

    return 0;
}