#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

User database[100]; // Assuming max 100 users in the database
int user_count = 0;

int find_user(const char *email) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(database[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void delete_user(int index) {
    if (index >= 0 && index < user_count) {
        for (int i = index; i < user_count - 1; ++i) {
            database[i] = database[i + 1];
        }
        --user_count;
    }
}

void handle_unsubscribe(const char *email) {
    int index = find_user(email);
    if (index != -1) {
        delete_user(index);
        printf("User unsubscribed successfully.\n");
    } else {
        printf("User is not subscribed.\n");
    }
}

int main() {
    // Simulate a GET request with an email parameter
    char email[] = "example@example.com";
    
    handle_unsubscribe(email);

    return 0;
}