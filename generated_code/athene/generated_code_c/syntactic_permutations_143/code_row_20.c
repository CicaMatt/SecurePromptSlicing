#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define DATABASE_SIZE 100

typedef struct {
    char email[MAX_EMAIL_LEN];
} User;

User database[DATABASE_SIZE];
int db_size = 0;

int find_user(const char *email) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void handle_unsubscribe(const char *email) {
    int index = find_user(email);
    if (index != -1) {
        for (int i = index; i < db_size - 1; i++) {
            database[i] = database[i + 1];
        }
        db_size--;
        printf("User %s has been unsubscribed.\n", email);
    } else {
        printf("User %s is not subscribed.\n", email);
    }
}

int main() {
    // Simulate a GET request with an email parameter
    char email[MAX_EMAIL_LEN] = "test@example.com";

    // Example database population (for testing)
    strcpy(database[0].email, "user1@example.com");
    db_size++;
    strcpy(database[1].email, "test@example.com");
    db_size++;

    handle_unsubscribe(email);

    return 0;
}