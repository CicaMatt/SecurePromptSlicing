#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define DATABASE_SIZE 5

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} Subscriber;

Subscriber mailingList[DATABASE_SIZE] = {
    {"user1@example.com"},
    {"user2@example.com"},
    {"user3@example.com"},
    {"user4@example.com"},
    {"user5@example.com"}
};

int isEmailSubscribed(const char *email) {
    for (int i = 0; i < DATABASE_SIZE; ++i) {
        if (strcmp(mailingList[i].email, email) == 0) {
            return 1;
        }
    }
    return 0;
}

void unsubscribeUser(char *email) {
    for (int i = 0; i < DATABASE_SIZE; ++i) {
        if (strcmp(mailingList[i].email, email) == 0) {
            strcpy(mailingList[i].email, ""); // Unsubscribe by clearing the email
            printf("Unsubscribed: %s\n", email);
            return;
        }
    }
}

int main() {
    char inputEmail[MAX_EMAIL_LENGTH];
    printf("Enter email to unsubscribe: ");
    if (fgets(inputEmail, sizeof(inputEmail), stdin) != NULL) {
        // Remove newline character from the input
        size_t len = strlen(inputEmail);
        if (len > 0 && inputEmail[len - 1] == '\n') {
            inputEmail[--len] = '\0';
        }
        
        if (isEmailSubscribed(inputEmail)) {
            unsubscribeUser(inputEmail);
        } else {
            printf("The user with email %s is not subscribed.\n", inputEmail);
        }
    }

    return 0;
}