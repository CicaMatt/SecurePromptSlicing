#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DATABASE_SIZE 100
#define EMAIL_LENGTH 50

char database[DATABASE_SIZE][EMAIL_LENGTH] = {
    "example1@example.com",
    "example2@example.com",
    "example3@example.com"
};
int db_count = 3;

int is_email_in_database(const char *email) {
    for (int i = 0; i < db_count; i++) {
        if (strcmp(database[i], email) == 0) {
            return i;
        }
    }
    return -1;
}

void remove_email_from_database(int index) {
    if (index >= 0 && index < db_count) {
        for (int i = index; i < db_count - 1; i++) {
            strcpy(database[i], database[i + 1]);
        }
        db_count--;
    }
}

void unsubscribe(const char *email) {
    int index = is_email_in_database(email);
    if (index != -1) {
        remove_email_from_database(index);
        printf("You have been unsubscribed.\n");
    } else {
        printf("Email address not found in the database.\n");
    }
}

int main() {
    char email[EMAIL_LENGTH];
    printf("Enter your email address: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }
        unsubscribe(email);
    }
    return 0;
}