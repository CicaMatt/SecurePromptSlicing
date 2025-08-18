#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

User database[] = {{"user1@example.com"}, {"user2@example.com"}};
int db_size = 2;

int find_user_index(const char *email) {
    for (int i = 0; i < db_size; ++i) {
        if (strcmp(database[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribe(const char *email) {
    int index = find_user_index(email);
    if (index != -1) {
        for (int i = index; i < db_size - 1; ++i) {
            database[i] = database[i + 1];
        }
        --db_size;
        printf("User with email %s has been unsubscribed and removed from the database.\n", email);
    } else {
        printf("The user with email %s is not subscribed to the mailing list.\n", email);
    }
}

int main() {
    char email_to_unsubscribe[MAX_EMAIL_LENGTH];
    printf("Enter email to unsubscribe: ");
    if (fgets(email_to_unsubscribe, sizeof(email_to_unsubscribe), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(email_to_unsubscribe);
        if (len > 0 && email_to_unsubscribe[len - 1] == '\n') {
            email_to_unsubscribe[len - 1] = '\0';
        }
        
        unsubscribe(email_to_unsubscribe);
    }

    return 0;
}