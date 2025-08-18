#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char email[256];
} User;

User users[MAX_USERS];
int user_count = 0;

void unsubscribe(const char *email) {
    int found = 0;
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].email, email) == 0) {
            // Shift all subsequent elements to the left
            for (int j = i; j < user_count - 1; j++) {
                users[j] = users[j + 1];
            }
            user_count--;
            found = 1;
            printf("User unsubscribed: %s\n", email);
            break;
        }
    }

    if (!found) {
        printf("User not subscribed: %s\n", email);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    unsubscribe(email);

    return 0;
}