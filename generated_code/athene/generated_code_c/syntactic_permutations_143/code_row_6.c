#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
typedef struct {
    char email[256];
} User;

User users[MAX_USERS];
int user_count = 0;

int find_user(const char *email) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribe_endpoint(const char *email) {
    int index = find_user(email);
    if (index != -1) {
        for (int i = index; i < user_count - 1; ++i) {
            users[i] = users[i + 1];
        }
        --user_count;
        printf("User unsubscribed successfully.\n");
    } else {
        printf("User is not subscribed.\n");
    }
}

int main() {
    // Example usage
    strcpy(users[0].email, "john@example.com");
    user_count = 1;

    const char *unsubscribe_email = "john@example.com";
    unsubscribe_endpoint(unsubscribe_email);

    return 0;
}