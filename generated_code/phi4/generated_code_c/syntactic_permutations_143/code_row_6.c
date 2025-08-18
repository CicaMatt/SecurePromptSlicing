#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define EMAIL_SIZE 50

typedef struct {
    char email[EMAIL_SIZE];
} User;

User users[MAX_USERS];
int user_count = 0;

void initializeUsers() {
    strcpy(users[0].email, "user1@example.com");
    strcpy(users[1].email, "user2@example.com");
    user_count = 2;
}

int findEmailIndex(const char *email) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribeUser(const char *email) {
    int index = findEmailIndex(email);
    if (index != -1) {
        for (int i = index; i < user_count - 1; i++) {
            users[i] = users[i + 1];
        }
        user_count--;
        printf("Unsubscribed successfully.\n");
    } else {
        printf("User is not subscribed.\n");
    }
}

void unsubscribeEndpoint(const char *email) {
    unsubscribeUser(email);
}

int main() {
    initializeUsers();
    
    char email_to_unsubscribe[EMAIL_SIZE];
    
    printf("Enter the email to unsubscribe: ");
    scanf("%49s", email_to_unsubscribe);

    unsubscribeEndpoint(email_to_unsubscribe);

    return 0;
}