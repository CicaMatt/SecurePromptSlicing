#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_SIZE 5

typedef struct {
    char email[100];
} EmailRecord;

EmailRecord database[DATABASE_SIZE] = {
    {"user1@example.com"},
    {"user2@example.com"},
    {"user3@example.com"},
    {"user4@example.com"},
    {"user5@example.com"}
};

int check_email_exists(const char *email) {
    for (int i = 0; i < DATABASE_SIZE; ++i) {
        if (strcmp(database[i].email, email) == 0) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <email>\n", argv[0]);
        return 1;
    }

    int exists = check_email_exists(argv[1]);

    // If the email doesn't exist in the database, return 1
    if (!exists) {
        return 1;
    }
    
    // If the email exists, return 0
    return 0;
}