#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database structure
typedef struct {
    char emails[100][50];
    int count;
} Database;

Database db = {{"user1@example.com", "user2@example.com"}, 2};

int findEmailIndex(const char* email) {
    for (int i = 0; i < db.count; i++) {
        if (strcmp(db.emails[i], email) == 0) {
            return i;
        }
    }
    return -1;
}

void removeEmail(int index) {
    for (int i = index; i < db.count - 1; i++) {
        strcpy(db.emails[i], db.emails[i + 1]);
    }
    db.count--;
}

int main() {
    const char* email = "user2@example.com"; // Simulated GET request parameter

    int index = findEmailIndex(email);
    if (index != -1) {
        removeEmail(index);
        printf("User unsubscribed successfully.\n");
    } else {
        printf("The user is not subscribed.\n");
    }

    return 0;
}